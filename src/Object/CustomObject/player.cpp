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


    this->vertexCount = 36;

    this->data_block_size = { 3, 3, 2 };



    this->data = new float[288] {
            //vertices
            -1, -1, -1,
            1, -1, -1,
            1,  1, -1,

            -1, -1, -1,
            1,  1, -1,
            -1,  1, -1,

            1,  1, -1,
            1,  1,  1,
            -1,  1,  1,

            1,  1, -1,
            -1,  1,  1,
            -1,  1, -1,

            -1,  1,  1,
            -1, -1,  1,
            -1, -1, -1,

            -1,  1,  1,
            -1, -1, -1,
            -1,  1, -1,

            -1, -1, -1,
            -1, -1,  1,
            1, -1,  1,

            -1, -1, -1,
            1, -1,  1,
            1, -1, -1,

            1,  1, -1,
            1, -1, -1,
            1, -1,  1,

            1,  1, -1,
            1, -1,  1,
            1,  1,  1,

            -1,  1,  1,
            1,  1,  1,
            1, -1,  1,

            -1,  1,  1,
            1, -1,  1,
            -1, -1,  1,

            //color
            1.0f, 0.5f, 0.2f,
            0.2f, 1.0f, 0.5f,
            0.5f, 0.2f, 1.0f,

            0.5f, 0.2f, 1.0f,
            1.0f, 0.5f, 0.2f,
            0.2f, 1.0f, 0.5f,

            0.5f, 0.2f, 1.0f,
            0.5f, 0.2f, 1.0f,
            1.0f, 0.5f, 0.2f,

            0.2f, 1.0f, 0.5f,
            0.5f, 0.2f, 1.0f,
            0.5f, 0.2f, 1.0f,

            1.0f, 0.5f, 0.2f,
            0.2f, 1.0f, 0.5f,
            0.5f, 0.2f, 1.0f,

            0.5f, 0.2f, 1.0f,
            1.0f, 0.5f, 0.2f,
            0.2f, 1.0f, 0.5f,

            0.5f, 0.2f, 1.0f,
            0.5f, 0.2f, 1.0f,
            1.0f, 0.5f, 0.2f,

            0.2f, 1.0f, 0.5f,
            0.5f, 0.2f, 1.0f,
            0.5f, 0.2f, 1.0f,

            1.0f, 0.5f, 0.2f,
            0.2f, 1.0f, 0.5f,
            0.5f, 0.2f, 1.0f,

            0.5f, 0.2f, 1.0f,
            1.0f, 0.5f, 0.2f,
            0.2f, 1.0f, 0.5f,

            0.5f, 0.2f, 1.0f,
            0.5f, 0.2f, 1.0f,
            1.0f, 0.5f, 0.2f,

            0.2f, 1.0f, 0.5f,
            0.5f, 0.2f, 1.0f,
            0.5f, 0.2f, 1.0f,


            //u, v
            //0
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            //1
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            //2
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            //3
            0.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,
            //4
            0.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,
            //5
            0.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,
            //6
            0.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,
            //7
            0.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,
            //8
            0.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,
            //9
            0.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,
            //10
            0.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,
            //11
            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f

    };

    this->vao->element_amount = 12; //6*2

    element = new GLuint[36];
    for (int i = 0; i < 36; ++i) {element[i] = i;}

    collider = new BoxCollider();
}

void player::bind() {
    this->shader = new
            Shader(
            "box.vert",
            nullptr, nullptr, nullptr,
            "box.frag");
    gpu_obj_t::bind();
//    return;
}

bool player::IsCollision(PhysicsObject *obj, glm::vec3& collisionVector) {
    bool coll = gpu_obj_t::IsCollision(obj, collisionVector);
//    cout << coll << endl;
    if(coll) state = ActionState::Floor;
//    else state = ActionState::Drop;
    return coll;
}
