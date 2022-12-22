//
// Created by 林士傑 on 2022/12/22.
//

#ifndef AMUSEMENTPARK_BOXCOLLIDER_H
#define AMUSEMENTPARK_BOXCOLLIDER_H

#include "ICollider.h"

class BoxCollider : public ICollider{
    glm::vec3 center = glm::vec3(0), size = glm::vec3(1);
public:
    BoxCollider();

    BoxCollider(const glm::vec3 &center, const glm::vec3 &size);

    bool IsCollision(ICollider *collider) override;

    bool IsCollision(BoxCollider *collider) override;

    bool IsCollision(BallCollider *collider) override;

    void Translate(glm::vec3 translate) override;

    void Scale(glm::vec3 scale) override;
};


#endif //AMUSEMENTPARK_BOXCOLLIDER_H
