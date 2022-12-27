//
// Created by 林士傑 on 2022/12/22.
//

#ifndef AMUSEMENTPARK_ICOLLIDER_H
#define AMUSEMENTPARK_ICOLLIDER_H

#pragma once

#include "glm/vec3.hpp"

class BoxCollider;
class BallCollider;

class ICollider {

public:
    virtual bool IsCollision(ICollider* collider, glm::vec3& collisionVector) = 0;
    virtual bool IsCollision(BoxCollider* collider, glm::vec3& collisionVector) = 0;
    virtual bool IsCollision(BallCollider* collider, glm::vec3& collisionVector) = 0;

    virtual void SetPosition(glm::vec3 position) = 0;
    virtual void Translate(glm::vec3 translate) = 0;
    virtual void Scale(glm::vec3 scale) = 0;
};


#endif //AMUSEMENTPARK_ICOLLIDER_H
