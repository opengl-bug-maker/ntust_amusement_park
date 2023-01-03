//
// Created by 林士傑 on 2023/1/2.
//

#include "SpreadSystem.h"

SpreadSystem::SpreadSystem(const glm::vec3 &startPosition, const glm::vec3 &moveDirection, const glm::vec3 &moveRandom)
        : StartPosition(startPosition), MoveDirection(moveDirection), MoveRandom(moveRandom) {}

const glm::vec3 &SpreadSystem::getStartPosition() const {
    return StartPosition;
}

const glm::vec3 &SpreadSystem::getMoveDirection() const {
    return MoveDirection;
}
