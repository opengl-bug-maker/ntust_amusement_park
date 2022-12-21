//
// Created by 林士傑 on 2022/12/9.
//

#ifndef AMUSEMENTPARK_ARCBALLCAMERA_H
#define AMUSEMENTPARK_ARCBALLCAMERA_H

#include "Camera.h"

class GameWindow;

class ArcBallCamera : public Camera {
    Quat start, now;

    enum {
        None,
        Rotate,
        Pan
    } mode;

    float panX, panY;

    void computeNow(const float nowX, const float nowY);

    void spin(float x, float y, float z);

protected:
    void down(const float x, const float y) override;

public:
    ArcBallCamera();

    void setup(float fieldOfView, float eyeZ, float isx, float isy, float isz) override;

    void reset() override;

    int handle(sf::Event e) override;

    glm::mat4 getPerspectiveMatrix() const override;

    glm::mat4 getModelViewMatrix() const override;

    glm::vec3 getEyePosition() const override;

    glm::vec3 getEyeDirection() const override;
};


#endif //AMUSEMENTPARK_ARCBALLCAMERA_H
