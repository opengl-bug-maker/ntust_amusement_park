//
// Created by 林士傑 on 2022/12/22.
//

#ifndef AMUSEMENTPARK_PLAYER_H
#define AMUSEMENTPARK_PLAYER_H

#include "gpu_object.h"
#include "Object/Collider/BoxCollider.h"

class player : public gpu_obj_t {
    void init() override;

public:
    enum ActionState {
        Floor = 0,
        Drop = 1,
        OnTrain = 2
    };

    ActionState state = ActionState::Drop;

    bool IsCollision(PhysicsObject *obj, glm::vec3& collisionVector) override;

    void bind() override;
    player();
};


#endif //AMUSEMENTPARK_PLAYER_H
