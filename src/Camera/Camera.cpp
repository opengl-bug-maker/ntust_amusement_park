//
// Created by 林士傑 on 2022/12/9.
//

#include "Camera.h"
#include "GameWindow.h"

Camera::Camera()
        :   fieldOfView(40),
            eyeX(0), eyeY(0), eyeZ(20),
            isx(0), isy(0), isz(0) {
}

void Camera::setup(float _fieldOfView, float _eyeZ,
      float _isx, float _isy, float _isz) {
    fieldOfView = _fieldOfView;
    eyeZ			= _eyeZ;
    eyeX			= 0;
    eyeY			= 0;
    isx			= _isx;
    isy			= _isy;
    isz			= _isz;


    reset();
//    spin(isx,isy,isz);
}

void Camera::down(const float x, const float y) {

}

void Camera::getMouseNDC(float& x, float& y) {
    // notice, we put everything into doubles so we can do the math
    float mx = (float) sf::Mouse::getPosition(*((sf::Window*)GameWindow::magic)).x;	// remeber where the mouse went down
    float my = (float) sf::Mouse::getPosition(*((sf::Window*)GameWindow::magic)).y;

    // we will assume that the viewport is the same as the window size
    float wd = GameWindow::magic->getSize().x;
    float hd = GameWindow::magic->getSize().y;

    // remember that FlTk has Y going the wrong way!
    my = hd-my;

    x = (mx / wd) * 2.0f - 1.f;
    y = (my / hd) * 2.0f - 1.f;
}

void Camera::reset() {

}

//void Camera::down(const float x, const float y) {
//    start = now * start;
//    now = Quat();		// identity
//
//    downX = x;
//    downY = y;
//
//    panX = 0;
//    panY = 0;
//}
//void Camera::reset() {
//    start.x = start.y = start.z = 0; start.w = 1;
//
//    now.x = now.y = now.z = 0; now.w = 1;
//}

//void Camera::spin(float x, float y, float z) {
//    // first, get rid of anything cached
//    start = now * start;
//    now = Quat();
//
//    float iw = x*x + y*y + z*z;
//    if (iw<1)
//        iw = sqrt(1-iw);
//    else
//        iw = 0;
//    Quat newq(x,y,z,iw);
//
//    newq.renorm();
//    start = newq * start;
//
//    start.renorm();
//}

//static void onUnitSphere(const float mx, const float my,
//                         float& x, float& y, float& z) {
//    x = mx;		// should divide radius
//    y = my;
//    float mag = x*x + y*y;
//    if (mag > 1.0f) {
//        float scale = 1.0f / ((float) sqrt(mag));
//        x *= scale;
//        y *= scale;
//        z = 0;
//    } else {
//        z = (float) sqrt(1 - mag);
//    }
//}

//void Camera::computeNow(const float nowX, const float nowY) {
//    if (mode==Rotate) {
//        float dx,dy,dz;
//        float mx,my,mz;
//        onUnitSphere(downX, downY, dx, dy, dz);
//        onUnitSphere(nowX, nowY, mx, my, mz);
//
//        // here we compute the quaternion between these two points
//        now.x = dy*mz - dz*my;
//        now.y = dz*mx - dx*mz;
//        now.z = dx*my - dy*mx;
//        now.w = dx*mx + dy*my + dz*mz;
//
//        now.renorm();		// just in case...
//    }
//    else if (mode==Pan) {
//        float dx = (nowX-downX) * eyeZ;
//        float dy = (nowY-downY) * eyeZ;
//
//        eyeX += panX - dx;
//        eyeY += panY - dy;
//        panX = dx;
//        panY = dy;
//    }
//}

int Camera::handle(sf::Event e) {
    return 0;
}

glm::mat4 Camera::getPerspectiveMatrix() const {
    return glm::mat4();
}

glm::mat4 Camera::getModelViewMatrix() const {
    return glm::mat4();
}

glm::vec3 Camera::getEyePosition() const {
    return glm::vec3();
}

glm::vec3 Camera::getEyeDirection() const {
    return glm::vec3();
}
