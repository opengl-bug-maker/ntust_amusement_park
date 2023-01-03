//
// Created by 林士傑 on 2023/1/2.
//

#ifndef AMUSEMENTPARK_SPREADSYSTEM_H
#define AMUSEMENTPARK_SPREADSYSTEM_H


#include "glm/vec3.hpp"

class SpreadSystem {
    glm::vec3 StartPosition;
    glm::vec3 MoveDirection;
    glm::vec3 MoveRandom;
public:
    SpreadSystem(const glm::vec3 &startPosition, const glm::vec3 &moveDirection, const glm::vec3 &moveRandom);

    const glm::vec3 &getStartPosition() const;

    const glm::vec3 &getMoveDirection() const;
};


#endif //AMUSEMENTPARK_SPREADSYSTEM_H
