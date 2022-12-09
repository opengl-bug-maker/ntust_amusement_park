//
// Created by 林士傑 on 2022/12/9.
//

#ifndef AMUSEMENTPARK_ARCBALLCAMERA_H
#define AMUSEMENTPARK_ARCBALLCAMERA_H

#include "Camera.h"

class GameWindow;

class ArcBallCamera : public Camera {
public:
    ArcBallCamera();

    int handle(sf::Event e) override;

    glm::mat4 getPerspectiveMatrix() const override;

    glm::mat4 getModelViewMatrix() const override;

    glm::vec3 getEyePosition() const override;

    glm::vec3 getEyeDirection() const override;
};


#endif //AMUSEMENTPARK_ARCBALLCAMERA_H
