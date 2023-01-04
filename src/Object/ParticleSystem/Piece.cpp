//
// Created by 林士傑 on 2023/1/2.
//

#include "Piece.h"
#include "GameWindow.h"

Piece::Piece() {
    Piece::init();
}

void Piece::init() {
    gpu_obj_t::init();

    this->vertexCount = 4;

    this->data_block_size = { 3, 2 };

    this->data = new float[20] {
            -1, -1, 0,
            1, -1, 0,
            1, 1, 0,
            -1, 1, 0,

//            0,0,0,
//            0,0,0,
//            0,0,0,
//            0,0,0,

            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
    };

    this->vao->element_amount = 2;

    element = new GLuint[6]{
        0, 1, 2,
        0, 2, 3
    };
}

void Piece::bind() {
    if (this->shader) return;

    this->shader = new Shader(
            "piece.vert",
            nullptr,
            nullptr,
            "piece.geom",
            "piece.frag"
    );

    SetTexture("../Images/particle.png");

    gpu_obj_t::bind();
}

void Piece::draw(glm::mat4 modelMatrix) {
    sf::Texture::bind(this->sf_texture);
    if(!visible)
        return;
    modelMatrix = modelMatrix * this->model_matrix;
    for(auto& child : children){
        child->draw(modelMatrix);
    }
    if(this->shader)
        this->shader->Use();
    else { return; }


    glUniform3fv(glGetUniformLocation(this->shader->Program, "cameraPosition")
            , 1, glm::value_ptr(GameWindow::magic->firstPersonCamera.getEyePosition()));

    glUniformMatrix4fv(
            glGetUniformLocation(this->shader->Program, "u_projection"), 1, GL_FALSE, glm::value_ptr(gpu_obj_t::projection_matrix));

    glUniformMatrix4fv(
            glGetUniformLocation(this->shader->Program, "u_view"), 1, GL_FALSE, glm::value_ptr(gpu_obj_t::view_matrix));

    glUniformMatrix4fv( //warning : model matrix name
            glGetUniformLocation(this->shader->Program, "u_model"), 1, GL_FALSE, &modelMatrix[0][0]);

    glBindVertexArray(vao->vao);
    glDrawElements(GL_TRIANGLES, vao->element_amount * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glUseProgram(0);
    sf::Texture::bind(nullptr);
}
