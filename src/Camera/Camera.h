//
// Created by 林士傑 on 2022/12/9.
//

#ifndef AMUSEMENTPARK_CAMERA_H
#define AMUSEMENTPARK_CAMERA_H

#include "Quat.h"
#include "SFML/Window/Event.hpp"

class GameWindow;

class Camera {
protected:

    float downX, downY;

    float eyeX, eyeY, eyeZ;

    float fieldOfView;

    float isx, isy, isz;

    virtual void down(const float x, const float y);

    void getMouseNDC(float& x, float& y);

public:

    Camera();

    virtual void setup(
            float fieldOfView = 40.0,
            float eyeZ = 8.0,
            float isx = 0, float isy = 0, float isz = 0
    );

    virtual void reset();

    virtual int handle(sf::Event e);

    virtual glm::mat4 getPerspectiveMatrix() const;

    virtual glm::mat4 getModelViewMatrix() const;

    virtual glm::vec3 getEyePosition() const;

    virtual glm::vec3 getEyeDirection() const;
};


#endif //AMUSEMENTPARK_CAMERA_H
