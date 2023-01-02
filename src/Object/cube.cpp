//
// Created by 林士傑 on 2022/12/7.
//

#include "cube.h"
#include "GameWindow.h"
cube::cube() {
    init();
}
// gpu_object -> simple object -> something
void cube::init() {
    gpu_obj_t::init();

    this->model_matrix = glm::scale(this->model_matrix, glm::vec3(1.0f, 1.0f, 1.0f));

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

void cube::bind() {
    if (this->shader) return;

    /*this->shader = new
            Shader(
            "explosion.vert",
            nullptr, nullptr, "explosion.gs",
            "explosion.frag");*/
    this->shader = new
        Shader(
            "box.vert",
            nullptr, nullptr, nullptr,
            "box.frag");
    this->shader->Use();
    //this->sf_texture.loadFromFile("X:/CS/2022ComputerGraphics/Projects/ntust_amusement_park/Images/uvtemplate.jpg");
    //this->texture = new Texture2D();
    //this->texture->set2dTexture("../Images/skybox/back.jpg");
    //this->texture->bind(0);
    //glUniform1i(glGetUniformLocation(this->shader->Program, "u_texture"), 0);

    glUniform1f(
        glGetUniformLocation(this->shader->Program, "start_time"), (GLfloat)(GameWindow::magic->nowTime.asSeconds()));

    gpu_obj_t::bind();
}

void cube::draw(glm::mat4 modelMatrix){
    if (!visible)
        return;
    this->shader->Use();
    glUniform1f(
        glGetUniformLocation(this->shader->Program, "now_time"), (GLfloat)(GameWindow::magic->nowTime.asSeconds()));
    glUniformMatrix4fv(
        glGetUniformLocation(this->shader->Program, "u_projection"), 1, GL_FALSE, glm::value_ptr(gpu_obj_t::projection_matrix));
    sf::Texture::bind(&this->sf_texture);
    gpu_obj_t::draw(modelMatrix);
    //gpu_obj_t::draw();
}
