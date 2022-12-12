//
// Created by 林士傑 on 2022/12/9.
//

#include "FirstPersonCamera.h"
#include "GameWindow.h"

FirstPersonCamera::FirstPersonCamera() : Camera() {

}

void FirstPersonCamera::lock() {
    sf::Mouse::setPosition(
            sf::Vector2i(GameWindow::magic->getSize().x * 0.5,
                         GameWindow::magic->getSize().y * 0.5)
                         , *GameWindow::magic);
    mode = Rotate;
    down(0, 0);
}

int FirstPersonCamera::handle(sf::Event e) {
    switch (e.type) {
        case sf::Event::MouseButtonPressed:
//            mode = None;
//            // right mouse button down
//            if (e.mouseButton.button == sf::Mouse::Right){
//                float x, y;
//                getMouseNDC(x,y);
//                // Compute the mouse position
//                down(x, y);
//                // Set up the mode
//                mode = sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) ? Pan : Rotate;
//                return 1;
//            }
            break;
        case sf::Event::MouseButtonReleased:
            if (mode != None) {
                mode = None;
                return 1;
            }
            break;
        case sf::Event::MouseMoved:
//            cout << "move!" << endl;
//            if(mode != None) { // we're taking the drags
                float x,y;
                getMouseNDC(x,y);
//                x *= ; y *= ;
                float xx;
                xx = ((x - downX) * downX < 0 ? 0.5f * x : -0.5f * x);
                float yy;
                yy = ((y - downY) * downY < 0 ? 0.5f * y : -0.5f * y);

                computeNow(xx + downX, yy + downY);

                down(x, y);
                if(abs(x) > 0.01 || abs(y) > 0.01)
                    sf::Mouse::setPosition(sf::Vector2i(GameWindow::magic->getSize().x * 0.5,GameWindow::magic->getSize().y * 0.5)
                        , *GameWindow::magic);
                return 1;
//            }
            break;
        case sf::Event::KeyPressed:
            switch (e.key.code) {
                case sf::Keyboard::W:
                    eyeX += moveSpeed * getEyeDirection()[0];
                    eyeY += moveSpeed * getEyeDirection()[1];
                    eyeZ += moveSpeed * getEyeDirection()[2];
                    return 1;
                case sf::Keyboard::A:
                    eyeX -= moveSpeed * getRightDirection()[0];
                    eyeY -= moveSpeed * getRightDirection()[1];
                    eyeZ -= moveSpeed * getRightDirection()[2];
                    return 1;
                case sf::Keyboard::S:
                    eyeX -= moveSpeed * getEyeDirection()[0];
                    eyeY -= moveSpeed * getEyeDirection()[1];
                    eyeZ -= moveSpeed * getEyeDirection()[2];
                    return 1;
                case sf::Keyboard::D:
                    eyeX += moveSpeed * getRightDirection()[0];
                    eyeY += moveSpeed * getRightDirection()[1];
                    eyeZ += moveSpeed * getRightDirection()[2];
                    return 1;
                case sf::Keyboard::LShift:
                    eyeX -= moveSpeed * getTopDirection()[0];
                    eyeY -= moveSpeed * getTopDirection()[1];
                    eyeZ -= moveSpeed * getTopDirection()[2];
                    return 1;
                case sf::Keyboard::Space:
                    eyeX += moveSpeed * getTopDirection()[0];
                    eyeY += moveSpeed * getTopDirection()[1];
                    eyeZ += moveSpeed * getTopDirection()[2];
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

glm::vec3 FirstPersonCamera::getEyePosition() const {
    return glm::vec4(eyeX, eyeY, eyeZ, 1);;
}

glm::vec3 FirstPersonCamera::getEyeDirection() const {
    glm::mat4 ModelView = (now * start).conjugate().toGLMMatrix();
    return ModelView * glm::vec4 (0, 0, -1, 0);
}

glm::vec3 FirstPersonCamera::getTopDirection() const {
    glm::mat4 ModelView = (now * start).conjugate().toGLMMatrix();
    return ModelView * glm::vec4 (0, 1, 0, 0);
}

glm::vec3 FirstPersonCamera::getRightDirection() const {
    glm::mat4 ModelView = (now * start).conjugate().toGLMMatrix();
    return ModelView * glm::vec4 (1, 0, 0, 0);
}