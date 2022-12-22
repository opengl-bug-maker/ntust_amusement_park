//
// Created by 林士傑 on 2022/12/22.
//

#include "BallCollider.h"

bool BallCollider::IsCollision(ICollider *collider) {
    return collider->IsCollision(this);
}

bool BallCollider::IsCollision(BoxCollider *collider) {
    return false;
}

bool BallCollider::IsCollision(BallCollider *collider) {
    return false;
}

void BallCollider::Translate(glm::vec3 translate) {

}

void BallCollider::Scale(glm::vec3 scale) {

}
