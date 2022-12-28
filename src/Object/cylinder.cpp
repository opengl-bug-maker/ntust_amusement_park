//
// Created by ªL¤h³Ç on 2022/12/7.
//

#include "cylinder.h"

cylinder::cylinder() {
    init();
}

void cylinder::init() {
    gpu_obj_t::init();

    //    this->model_matrix;
    //
    //    this->vertexCount;
    //
    //    this->data_block_size;
    //
    //    this->data;
    //
    //    this->vao->element_amount;
    //
    //    element;
}

void cylinder::bind() {
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
