//
// Created by 林士傑 on 2022/12/9.
//

#include "ArcBallCamera.h"
#include "GameWindow.h"

ArcBallCamera::ArcBallCamera() : Camera(),
        mode(None),
        panX(0), panY(0){

}

void ArcBallCamera::setup(float fieldOfView, float eyeZ, float isx, float isy, float isz) {
    Camera::setup(fieldOfView, eyeZ, isx, isy, isz);
    reset();
    spin(isx,isy,isz);
}

static void onUnitSphere(const float mx, const float my,
                         float& x, float& y, float& z) {
    x = mx;		// should divide radius
    y = my;
    float mag = x*x + y*y;
    if (mag > 1.0f) {
        float scale = 1.0f / ((float) sqrt(mag));
        x *= scale;
        y *= scale;
        z = 0;
    } else {
        z = (float) sqrt(1 - mag);
    }
}

void ArcBallCamera::computeNow(const float nowX, const float nowY) {
    if (mode==Rotate) {
        float dx,dy,dz;
        float mx,my,mz;
        onUnitSphere(downX, downY, dx, dy, dz);
        onUnitSphere(nowX, nowY, mx, my, mz);

        // here we compute the quaternion between these two points
        now.x = dy*mz - dz*my;
        now.y = dz*mx - dx*mz;
        now.z = dx*my - dy*mx;
        now.w = dx*mx + dy*my + dz*mz;

        now.renorm();		// just in case...
    }
    else if (mode==Pan) {
        float dx = (nowX-downX) * eyeZ;
        float dy = (nowY-downY) * eyeZ;

        eyeX += panX - dx;
        eyeY += panY - dy;
        panX = dx;
        panY = dy;
    }
}

void ArcBallCamera::spin(float x, float y, float z) {
    // first, get rid of anything cached
    start = now * start;
    now = Quat();

    float iw = x*x + y*y + z*z;
    if (iw<1)
        iw = sqrt(1-iw);
    else
        iw = 0;
    Quat newq(x,y,z,iw);

    newq.renorm();
    start = newq * start;

    start.renorm();
}

void ArcBallCamera::down(const float x, const float y) {
    start = now * start;
    now = Quat();		// identity

    downX = x;
    downY = y;

    panX = 0;
    panY = 0;
}

void ArcBallCamera::reset() {
    start.x = start.y = start.z = 0; start.w = 1;

    now.x = now.y = now.z = 0; now.w = 1;
}


int ArcBallCamera::handle(sf::Event e) {
    switch (e.type) {
        case sf::Event::MouseWheelMoved:
            if(abs(e.mouseWheel.delta) < 1) break;
            eyeZ *= (e.mouseWheel.delta < 0) ? 1.1f : 1/1.1f;
            return 1;
        case sf::Event::MouseButtonPressed:
            mode = None;
            // right mouse button down
            if (e.mouseButton.button == sf::Mouse::Right){
                float x, y;
                getMouseNDC(x,y);
                // Compute the mouse position
                down(x, y);
                // Set up the mode
                mode = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) ? Pan : Rotate;
                return 1;
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (mode != None) {
                mode = None;
                return 1;
            }
            break;
        case sf::Event::MouseMoved:
            if(mode != None) { // we're taking the drags
                float x,y;
                getMouseNDC(x,y);
                computeNow(x,y);
                return 1;
            }
            break;
        default:
            break;
    }
    return 0;
}

glm::mat4 ArcBallCamera::getPerspectiveMatrix() const{
    double f = 1/tan(fieldOfView / 360.0 * 3.141519265358979);
    double aspect = ((double) GameWindow::magic->getSize().x) / ((double) GameWindow::magic->getSize().y);

    return glm::mat4(
            f / aspect, 0, 0, 0,
            0, f, 0, 0,
            0, 0, -1.00020002f, -1,
            0, 0, -0.200020002f, 0
    );
}

glm::mat4 ArcBallCamera::getModelViewMatrix() const {
    glm::mat4 ModelView = glm::mat4(1);
    ModelView = glm::translate(ModelView, glm::vec3(-eyeX, -eyeY, -eyeZ));

    Quat qAll = now * start;
    qAll = qAll.conjugate();
    glm::mat4 q = qAll.toGLMMatrix();

    ModelView = ModelView * q;
    return ModelView;
}

glm::vec3 ArcBallCamera::getEyePosition() const {
    glm::mat4 model = getModelViewMatrix();
    model = glm::inverse(model);
    glm::vec4 eyePosition = glm::vec4(0, 0, 0, 1.0);
    eyePosition = model * eyePosition;
    return eyePosition;
}

glm::vec3 ArcBallCamera::getEyeDirection() const {
    Quat qAll = now * start;
    glm::mat4 q = qAll.toGLMMatrix();

    glm::vec4 direction = glm::vec4 (0, 0, -1, 0);
    direction = q * direction;
    return direction;
}
