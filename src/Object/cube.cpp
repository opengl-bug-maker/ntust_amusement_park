//
// Created by 林士傑 on 2022/12/7.
//

#include "cube.h"
cube::cube() {
    init();
}
// gpu_object -> simple object -> something
void cube::init() {
    gpu_obj_t::init();

    this->model_matrix = glm::scale(this->model_matrix, glm::vec3(1.0f, 1.0f, 1.0f));

    this->vertexCount = 8;

    this->data_block_size = { 3, 3, 2};

    this->data = new float[] {
            //vertices
        -1, -1, -1,
            1, -1, -1,
            1, 1, -1,
            -1, 1, -1,
            -1, 1, 1,
            1, 1, 1,
            1, -1, 1,
            -1, -1, 1,

            //color
            1.0f, 0.5f, 0.2f,
            0.2f, 1.0f, 0.5f,
            0.5f, 0.2f, 1.0f,
            0.5f, 0.2f, 1.0f,
            1.0f, 0.5f, 0.2f,
            0.2f, 1.0f, 0.5f,
            0.5f, 0.2f, 1.0f,
            0.5f, 0.2f, 1.0f,

            //u, v
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,

            1.0f, 0.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f

    };

    this->vao->element_amount = 12;

    element = new GLuint[]{
        0, 1, 2,
        0, 2, 3,
        2, 5, 4,
        2, 4, 3,
        4, 7, 0,
        4, 0, 3,
        0, 7, 6,
        0, 6, 1,
        2, 1, 6,
        2, 6, 5,
        4, 5, 6,
        4, 6, 7
    };

    collider = new BoxCollider();
}

void cube::bind() {
    if (this->shader) return;

    this->shader = new
            Shader(
            "box.vert",
            nullptr, nullptr, nullptr,
            "box.frag");
    this->texture = new Texture2D();
    this->texture->set2dTexture("../Images/skybox/back.jpg");
    this->texture->bind(0);
    glUniform1i(glGetUniformLocation(this->shader->Program, "u_texture"), 0);
    gpu_obj_t::bind();
}