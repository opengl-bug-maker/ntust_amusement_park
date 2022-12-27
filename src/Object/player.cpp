//
// Created by 林士傑 on 2022/12/22.
//

#include "player.h"

player::player() {
    init();
}

void player::init() {
    gpu_obj_t::init();

    visible = false;

    collider = new BoxCollider();
}

void player::bind() {
    return;
}

bool player::IsCollision(PhysicsObject *obj, glm::vec3& collisionVector) {
    bool coll = gpu_obj_t::IsCollision(obj, collisionVector);
//    cout << coll << endl;
    if(coll) state = ActionState::Floor;
//    else state = ActionState::Drop;
    return coll;
}
