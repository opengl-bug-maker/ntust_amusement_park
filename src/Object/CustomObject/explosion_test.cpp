//
// Created by �L�h�� on 2022/12/7.
//

#include "explosion_test.h"
#include "GameWindow.h"
explosion_test_t::explosion_test_t() {
    init();
}
// gpu_object -> simple object -> something
void explosion_test_t::init() {
    gpu_obj_t::init();

    this->model_matrix = glm::scale(this->model_matrix, glm::vec3(1.0f, 1.0f, 1.0f));

    this->vertexCount = 3;

    this->data_block_size = { 3, 3, 2 };



    this->data = new float[24] {
        //vertices
        -1, -1, -1,
            1, -1, -1,
            1, 1, -1,


            //color
            1.0f, 0.5f, 0.2f,
            0.2f, 1.0f, 0.5f,
            0.5f, 0.2f, 1.0f,



            //u, v
            0.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 0.0f
    };

    this->vao->element_amount = 3; //6*2

    element = new GLuint[1];
    for (int i = 0; i < 1; ++i) { element[i] = i; }

    collider = new BoxCollider();
}

void explosion_test_t::bind() {
    if (this->shader) return;

    this->shader = new
            Shader(
            "explosion.vert",
            nullptr, nullptr, "explosion.geom",
            "explosion.frag");
//    this->shader = new
//        Shader(
//            "box.vert",
//            nullptr, nullptr, nullptr,
//            "box.frag");
    this->shader->Use();
    SetTexture("../Images/uvtemplate.jpg");
    //this->texture = new Texture2D();
    //this->texture->set2dTexture("../Images/skybox/back.jpg");
    //this->texture->bind(0);
    //glUniform1i(glGetUniformLocation(this->shader->Program, "u_texture"), 0);

    glUniform1f(
        glGetUniformLocation(this->shader->Program, "start_time"), (GLfloat)(GameWindow::magic->nowTime.asSeconds()));

    gpu_obj_t::bind();
}

void explosion_test_t::draw(glm::mat4 modelMatrix) {
    if (!visible)
        return;
    this->shader->Use();
    glUniform1f(
        glGetUniformLocation(this->shader->Program, "now_time"), (GLfloat)(GameWindow::magic->nowTime.asSeconds()));
    glUniformMatrix4fv(
        glGetUniformLocation(this->shader->Program, "u_projection"), 1, GL_FALSE, glm::value_ptr(gpu_obj_t::projection_matrix));
    sf::Texture::bind(this->sf_texture);
    gpu_obj_t::draw(modelMatrix);
    //gpu_obj_t::draw();
}
