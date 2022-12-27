//
// Created by 林士傑 on 2022/12/9.
//

#ifndef AMUSEMENTPARK_FIRSTPERSONCAMERA_H
#define AMUSEMENTPARK_FIRSTPERSONCAMERA_H

#include "Camera.h"

class GameWindow;

class FirstPersonCamera : public Camera {
private:
    double theta = 0;// 0 ~ 360
    double phi = 0; // -90 ~ 90
    float moveSpeed = 1.0f;

protected:
    void down(const float x, const float y) override;

public:
    FirstPersonCamera();

    void reset() override;

    int handle(sf::Event e) override;

    void lock();

    void setPosition(glm::vec3 position);

    glm::mat4 getPerspectiveMatrix() const override;

    glm::mat4 getModelViewMatrix() const override;

    glm::vec3 getEyePosition() const override;

    glm::vec3 getEyeDirection() const override;

    glm::vec3 getTopDirection() const;

    glm::vec3 getRightDirection() const;
};


#endif //AMUSEMENTPARK_FIRSTPERSONCAMERA_H
