//
// Created by 林士傑 on 2022/12/7.
//

#include "cube.h"
cube::cube() {
    init();
}

cube::cube(GLfloat *input_data) : gpu_obj_t(input_data) {
    init();
}

void cube::init() {
    gpu_obj_t::init();

    this->model_matrix = glm::scale(this->model_matrix, glm::vec3(1.0f, 1.0f, 1.0f));

    this->vertexCount = 4;

    this->data_block_size = { 3, 3 };

    this->data = new float[] {
            //vertices
            -0.5,  -1, 0,
            0.5, -1, 0,
            0.5, 1, 0,
            -0.5, 1, 0,

            //color
            1.0f, 0.5f, 0.2f,
            0.2f, 1.0f, 0.5f,
            0.5f, 0.2f, 1.0f,
            0.5f, 0.2f, 1.0f,

    };

    this->vao->element_amount = 2;

    element = new GLuint[]{
        0, 1, 2,
        0, 2, 3
    };
}

void cube::bind() {
    if (this->shader) return;

    this->shader = new
            Shader(
            "test.vert",
            nullptr, nullptr, nullptr,
            "test.frag");

    gpu_obj_t::bind();
}