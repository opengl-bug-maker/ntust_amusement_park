//
// Created by 林士傑 on 2022/12/22.
//

#include "BoxCollider.h"

BoxCollider::BoxCollider() {}

BoxCollider::BoxCollider(const glm::vec3 &center, const glm::vec3 &size) : center(center), size(size) {}

bool BoxCollider::IsCollision(ICollider *collider, glm::vec3& collisionVector) {
    return collider->IsCollision(this, collisionVector);
}

bool BoxCollider::IsCollision(BoxCollider *collider, glm::vec3& collisionVector) {
    glm::vec3 _center = center - collider->center;
    glm::vec3 _size = size + collider->size;

    float mins[6] = {
            _size[0] + _center[0],
            _size[0] - _center[0],
            _size[1] + _center[1],
            _size[1] - _center[1],
            _size[2] + _center[2],
            _size[2] - _center[2]
    };

    float min = mins[0];
    int minIndex = 0;
    for(int i = 0; i < 6; i++) {
        if (min > mins[i]) {
            min = mins[i];
            minIndex = i;
        }
    }

    switch (minIndex) {
        case 0:
            collisionVector = glm::vec3(min, 0, 0);
            break;
        case 1:
            collisionVector = glm::vec3(-min, 0, 0);
            break;
        case 2:
            collisionVector = glm::vec3(0, min, 0);
            break;
        case 3:
            collisionVector = glm::vec3(0, -min, 0);
            break;
        case 4:
            collisionVector = glm::vec3(0, 0, min);
            break;
        case 5:
            collisionVector = glm::vec3(0, 0, -min);
            break;
        default:
            collisionVector = glm::vec3(0, 0, 0);
            break;
    }

//    if(min == mins[0]){
//        collisionVector = glm::vec3(min, 0, 0);
//    }else if(min == mins[1]){
//        collisionVector = glm::vec3(-min, 0, 0);
//    }else if(min == mins[2]){
//        collisionVector = glm::vec3(0, min, 0);
//    }else if(min == mins[3]){
//        collisionVector = glm::vec3(0, -min, 0);
//    }else if(min == mins[4]){
//        collisionVector = glm::vec3(0, 0, min);
//    }else if(min == mins[5]){
//        collisionVector = glm::vec3(0, 0, -min);
//    }



    return (
            _size[0] >= _center[0] &&
            -_size[0] <= _center[0] &&
            _size[1] >= _center[1] &&
            -_size[1] <= _center[1] &&
            _size[2] >= _center[2] &&
            -_size[2] <= _center[2]
            );
}

bool BoxCollider::IsCollision(BallCollider *collider, glm::vec3& collisionVector) {
    return false;
}

void BoxCollider::SetPosition(glm::vec3 position) {
    center = position;
}

void BoxCollider::Translate(glm::vec3 translate) {
    center += translate;
}

void BoxCollider::Scale(glm::vec3 scale) {
    size *= scale;
    int a = 0;
}
