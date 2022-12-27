//
// Created by 林士傑 on 2022/12/22.
//

#include "BallCollider.h"

bool BallCollider::IsCollision(ICollider *collider, glm::vec3& collisionVector) {
    return collider->IsCollision(this, collisionVector);
}

bool BallCollider::IsCollision(BoxCollider *collider, glm::vec3& collisionVector) {
    return false;
}

bool BallCollider::IsCollision(BallCollider *collider, glm::vec3& collisionVector) {
    return false;
}

void BallCollider::Translate(glm::vec3 translate) {

}

void BallCollider::Scale(glm::vec3 scale) {

}
