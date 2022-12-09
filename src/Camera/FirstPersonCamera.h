//
// Created by 林士傑 on 2022/12/9.
//

#ifndef AMUSEMENTPARK_FIRSTPERSONCAMERA_H
#define AMUSEMENTPARK_FIRSTPERSONCAMERA_H

#include "Camera.h"

class GameWindow;

class FirstPersonCamera : public Camera {

    float moveSpeed = 1.0f;
public:
    FirstPersonCamera();

    int handle(sf::Event e) override;

    glm::mat4 getPerspectiveMatrix() const override;

    glm::mat4 getModelViewMatrix() const override;

    glm::vec3 getEyePosition() const override;

    glm::vec3 getEyeDirection() const override;
};


#endif //AMUSEMENTPARK_FIRSTPERSONCAMERA_H
