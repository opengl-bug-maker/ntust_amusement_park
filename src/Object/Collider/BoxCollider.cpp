//
// Created by 林士傑 on 2022/12/22.
//

#include "BoxCollider.h"

BoxCollider::BoxCollider() {}

BoxCollider::BoxCollider(const glm::vec3 &center, const glm::vec3 &size) : center(center), size(size) {}

bool BoxCollider::IsCollision(ICollider *collider) {
    return collider->IsCollision(this);
}

bool BoxCollider::IsCollision(BoxCollider *collider) {
    glm::vec3 _center = center - collider->center;
    glm::vec3 _size = size + collider->size;
    return (
            _size[0] >= _center[0] &&
            -_size[0] <= _center[0] &&
            _size[1] >= _center[1] &&
            -_size[1] <= _center[1] &&
            _size[2] >= _center[2] &&
            -_size[2] <= _center[2]
            );
}

bool BoxCollider::IsCollision(BallCollider *collider) {
    return false;
}

void BoxCollider::Translate(glm::vec3 translate) {
    center += translate;
}

void BoxCollider::Scale(glm::vec3 scale) {
    size *= scale;
}
