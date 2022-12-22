//
// Created by 林士傑 on 2022/12/22.
//

#ifndef AMUSEMENTPARK_BALLCOLLIDER_H
#define AMUSEMENTPARK_BALLCOLLIDER_H

#include "ICollider.h"

class BallCollider : public ICollider {
public:
    bool IsCollision(ICollider *collider) override;

    bool IsCollision(BoxCollider *collider) override;

    bool IsCollision(BallCollider *collider) override;

    void Translate(glm::vec3 translate) override;

    void Scale(glm::vec3 scale) override;
};


#endif //AMUSEMENTPARK_BALLCOLLIDER_H
