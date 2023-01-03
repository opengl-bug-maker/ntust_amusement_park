//
// Created by 林士傑 on 2023/1/1.
//

#include "ParticleSystem.h"


template<typename T>
ParticleSystem<T>::ParticleSystem() {
    instance = T();
    instancePtr = &instance;
    ParticleSystem<T>::init();
}

template<typename T>
void ParticleSystem<T>::init() {
    gpu_obj_t::init();

    this->vertexCount = T::vertexCount;
//
    this->data_block_size = {};
//
//    this->data;
//
//    this->vao->element_amount;
//
//    element;
}

template<typename T>
void ParticleSystem<T>::bind() {
    if (this->shader) return;

//    this->shader = new Shader(
//            nullptr,
//            nullptr,
//            nullptr,
//            nullptr,
//            nullptr
//    );

//    this->shader = new Shader(
//            "piece.vert",
//            nullptr,
//            nullptr,
//            "piece.geom",
//            "piece.frag"
//    );

    gpu_obj_t::bind();
}

template<typename T>
void ParticleSystem<T>::draw(glm::mat4 modelMatrix) {
    gpu_obj_t::draw(modelMatrix);
}

