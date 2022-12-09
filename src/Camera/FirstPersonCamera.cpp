//
// Created by 林士傑 on 2022/12/9.
//

#include "FirstPersonCamera.h"
#include "GameWindow.h"

FirstPersonCamera::FirstPersonCamera() : Camera() {

}

int FirstPersonCamera::handle(sf::Event e) {
    switch (e.type) {
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
        case sf::Event::KeyPressed:
            switch (e.key.code) {
                case sf::Keyboard::W:
                    eyeZ -= moveSpeed;
                    return 1;
                case sf::Keyboard::A:
                    eyeX -= moveSpeed;
                    return 1;
                case sf::Keyboard::S:
                    eyeZ += moveSpeed;
                    return 1;
                case sf::Keyboard::D:
                    eyeX += moveSpeed;
                    return 1;
                case sf::Keyboard::LShift:
                    eyeY -= moveSpeed;
                    return 1;
                case sf::Keyboard::Space:
                    eyeY += moveSpeed;
                    return 1;
                default :
                    break;
            }
        default:
            break;
    }
    return 0;
}

glm::mat4 FirstPersonCamera::getPerspectiveMatrix() const{
    double f = 1/tan(fieldOfView / 360.0 * 3.141519265358979);
    double aspect = ((double) GameWindow::magic->getSize().x) / ((double) GameWindow::magic->getSize().y);

    return glm::mat4(
            f / aspect, 0, 0, 0,
            0, f, 0, 0,
            0, 0, -1.00020002f, -1,
            0, 0, -0.200020002f, 0
    );
}

glm::mat4 FirstPersonCamera::getModelViewMatrix() const {
    glm::mat4 ModelView = (now * start).toGLMMatrix();
    ModelView = glm::translate(ModelView, glm::vec3(-eyeX, -eyeY, -eyeZ));
    return ModelView;
}

//todo eyePosition
glm::vec3 FirstPersonCamera::getEyePosition() const {
    return glm::vec4(eyeX, eyeY, eyeZ, 1);;
}

glm::vec3 FirstPersonCamera::getEyeDirection() const {
    glm::vec4 direction = glm::vec4 (0, 0, 1, 0);
    direction = getModelViewMatrix() * direction;
    return direction;
}
