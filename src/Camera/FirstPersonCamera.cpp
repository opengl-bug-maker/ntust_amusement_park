//
// Created by 林士傑 on 2022/12/9.
//

#include "FirstPersonCamera.h"
#include "GameWindow.h"

FirstPersonCamera::FirstPersonCamera() : Camera() {

}

void FirstPersonCamera::down(const float x, const float y) {
    downX = x;
    downY = y;
}

void FirstPersonCamera::lock() {
    sf::Mouse::setPosition(
            sf::Vector2i(GameWindow::magic->getSize().x * 0.5,
                         GameWindow::magic->getSize().y * 0.5)
                         , *GameWindow::magic);
    down(0, 0);
}

void FirstPersonCamera::reset() {
    downX = 0;
    downY = 0;
    theta = 0;
    phi = 0;
}

int FirstPersonCamera::handle(sf::Event e) {
    switch (e.type) {
        case sf::Event::MouseButtonPressed:
            break;
        case sf::Event::MouseButtonReleased:
            break;
        case sf::Event::MouseMoved:
            float x,y;
            getMouseNDC(x,y);

            double deltaX; deltaX = x - downX;
            double deltaY; deltaY = y - downY;

            phi -= deltaY * 10;
            if(phi >= 89.9) phi = 89.9;
            if(phi <= -89.9) phi = -89.9;

            double mul; mul = cos(phi * 0.01745329252);

            theta += deltaX * 10 / mul;

            down(x, y);

            if(abs(x) > 0.01 || abs(y) > 0.01 )
                lock();
            return 1;
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
//    double st = sin(theta * 0.01745329252); // 3.14 / 180
//    double ct = cos(theta * 0.01745329252);
//    double sp = sin(phi   * 0.01745329252);
//    double cp = cos(phi   * 0.01745329252);
    double sp = sin(theta * 0.01745329252); // 3.14 / 180
    double cp = cos(theta * 0.01745329252);
    double st = sin(phi   * 0.01745329252);
    double ct = cos(phi   * 0.01745329252);

    glm::mat4 ModelView = glm::mat4(
            cp,  st * sp, -ct * sp, 0,
             0,       ct,       st, 0,
            sp, -st * cp, ct * cp, 0,
             0,        0,       0,1
            );
    ModelView = glm::translate(ModelView, glm::vec3(-eyeX, -eyeY, -eyeZ));
    return ModelView;
}

glm::vec3 FirstPersonCamera::getEyePosition() const {
    return glm::vec4(eyeX, eyeY, eyeZ, 1);;
}

glm::vec3 FirstPersonCamera::getEyeDirection() const {
    glm::mat4 ModelView = glm::inverse(getModelViewMatrix());
    return ModelView * glm::vec4 (0, 0, -1, 0);
}

glm::vec3 FirstPersonCamera::getTopDirection() const {
    glm::mat4 ModelView = glm::inverse(getModelViewMatrix());
    return ModelView * glm::vec4 (0, 1, 0, 0);
}

glm::vec3 FirstPersonCamera::getRightDirection() const {
    glm::mat4 ModelView = glm::inverse(getModelViewMatrix());
    return ModelView * glm::vec4 (1, 0, 0, 0);
}