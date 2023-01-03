//
// Created by 林士傑 on 2022/12/22.
//

#ifndef AMUSEMENTPARK_BOXCOLLIDER_H
#define AMUSEMENTPARK_BOXCOLLIDER_H

#include "ICollider.h"

class BoxCollider : public ICollider{
public:
    glm::vec3 center = glm::vec3(0), size = glm::vec3(1);
    BoxCollider();

    BoxCollider(const glm::vec3 &center, const glm::vec3 &size);

    bool IsCollision(ICollider *collider, glm::vec3& collisionVector) override;

    bool IsCollision(BoxCollider *collider, glm::vec3& collisionVector) override;

    bool IsCollision(BallCollider *collider, glm::vec3& collisionVector) override;

    void SetPosition(glm::vec3 position) override;

    void Translate(glm::vec3 translate) override;

    void Scale(glm::vec3 scale) override;
};


#endif //AMUSEMENTPARK_BOXCOLLIDER_H
