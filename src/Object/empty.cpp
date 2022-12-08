//
// Created by 林士傑 on 2022/12/7.
//

#include "empty.h"

empty::empty() {
    init();
}

void empty::init() {
    gpu_obj_t::init();

    this->model_matrix;

    this->vertexCount;

    this->data_block_size;

    this->data;

    this->vao->element_amount;

    element;
}

void empty::bind() {
    if (this->shader) return;

    this->shader = new Shader(
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr
            );

    gpu_obj_t::bind();
}
