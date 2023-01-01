//
// Created by ªL¤h³Ç on 2022/12/7.
//
#pragma once

#include "gpu_object.h"
#include "Object/Collider/BoxCollider.h"

class explosion_test_t : public gpu_obj_t {
    void init() override;

public:
    void bind() override;
    void draw(glm::mat4 modelMatrix = glm::mat4(1)) override;
    explosion_test_t();
};



