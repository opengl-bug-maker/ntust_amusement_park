//
// Created by 林士傑 on 2022/12/9.
//

#include "ArcBallCamera.h"
#include "GameWindow.h"

ArcBallCamera::ArcBallCamera() : Camera() {

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
