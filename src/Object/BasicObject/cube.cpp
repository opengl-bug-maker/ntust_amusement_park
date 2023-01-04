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

    this->data_block_size = { 3,3,2, 3}; //vs, nor, uv, color
    //this->data_block_size = { 3,3,2};



    this->data = new float[1000] {
            //vertices
         -1, -1, -1,  //neg z (back)
          1, -1, -1,
          1,  1, -1,
         -1, -1, -1,
          1,  1, -1,
         -1,  1, -1,

          1,  1, -1,   //top
          1,  1,  1,
         -1,  1,  1,
          1,  1, -1,
         -1,  1,  1,
         -1,  1, -1,

         -1,  1,  1, //neg x (left side)
         -1, -1,  1,
         -1, -1, -1,
         -1,  1,  1,
         -1, -1, -1,
         -1,  1, -1,
         
         -1, -1, -1, //bottom
         -1, -1,  1,
          1, -1,  1,
         -1, -1, -1,
          1, -1,  1,
          1, -1, -1,
         
          1,  1, -1, //pos x right side
          1, -1, -1,
          1, -1,  1,
          1,  1, -1,
          1, -1,  1,
          1,  1,  1,

         -1,  1,  1, //pos z
          1,  1,  1,
          1, -1,  1,
         -1,  1,  1,
          1, -1,  1,
         -1, -1,  1,



            //normal
         0, 0, -1, //back
         0, 0, -1,
         0, 0, -1,
         0, 0, -1,
         0, 0, -1,
         0, 0, -1,

         0, 1, 0, //top
         0, 1, 0,
         0, 1, 0,
         0, 1, 0,
         0, 1, 0,
         0, 1, 0,

         -1, 0, 0,// left side
         -1, 0, 0,
         -1, 0, 0,
         -1, 0, 0,
         -1, 0, 0,
         -1, 0, 0,

         0, -1, 0, //bottom
         0, -1, 0,
         0, -1, 0,
         0, -1, 0,
         0, -1, 0,
         0, -1, 0,

         1, 0, 0, //right
         1, 0, 0,
         1, 0, 0,
         1, 0, 0,
         1, 0, 0,
         1, 0, 0,

         0, 0, 1, //front
         0, 0, 1,
         0, 0, 1,

         0, 0, 1,
         0, 0, 1,
         0, 0, 1,
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
         1.0f, 0.0f,
         0.0f, 1.0f,
         0.0f, 0.0f,
            //4
         1.0f, 0.0f,
         1.0f, 1.0f,
         0.0f, 1.0f,
            //5
         1.0f, 0.0f,
         0.0f, 1.0f,
         0.0f, 0.0f,
            //6
         0.0f, 0.0f,
         0.0f, 1.0f,
         1.0f, 1.0f,
            //7
         0.0f, 0.0f,
         1.0f, 1.0f,
         0.0f, 1.0f,
            //8
         1.0f, 0.0f,
         1.0f, 1.0f,
         0.0f, 1.0f,
            //9
         1.0f, 0.0f,
         0.0f, 1.0f,
         0.0f, 0.0f,
            //10
         0.0f, 0.0f,
         1.0f, 0.0f,
         1.0f, 1.0f,
            //11
         0.0f, 0.0f,
         1.0f, 1.0f,
         0.0f, 1.0f,
            //color
         0.3f, 1.0f, 0.2f,
         0.0f, 0.7, 0.4f,
         1.0f, 0.4f, 0.2f,

         0.3f, 1.0f, 0.2f,
         0.0f, 0.7, 0.4f,
         1.0f, 0.4f, 0.2f,

         0.3f, 1.0f, 0.2f,
         0.0f, 0.7, 0.4f,
         1.0f, 0.4f, 0.2f,

         0.3f, 1.0f, 0.2f,
         0.0f, 0.7, 0.4f,
         1.0f, 0.4f, 0.2f,

         0.3f, 1.0f, 0.2f,
         0.0f, 0.7, 0.4f,
         1.0f, 0.4f, 0.2f,

         0.3f, 1.0f, 0.2f,
         0.0f, 0.7, 0.4f,
         1.0f, 0.4f, 0.2f,

         0.3f, 1.0f, 0.2f,
         0.0f, 0.7, 0.4f,
         1.0f, 0.4f, 0.2f,

         0.3f, 1.0f, 0.2f,
         0.0f, 0.7, 0.4f,
         1.0f, 0.4f, 0.2f,

         0.3f, 1.0f, 0.2f,
         0.0f, 0.7, 0.4f,
         1.0f, 0.4f, 0.2f,

         0.3f, 1.0f, 0.2f,
         0.0f, 0.7, 0.4f,
         1.0f, 0.4f, 0.2f,

         0.3f, 1.0f, 0.2f,
         0.0f, 0.7, 0.4f,
         1.0f, 0.4f, 0.2f,

         0.3f, 1.0f, 0.2f,
         0.0f, 0.7, 0.4f,
         1.0f, 0.4f, 0.2f

    };

    this->vao->element_amount = 36; //6*2

    element = new GLuint[36];
    for (int i = 0; i <36; ++i) {element[i] = i;}

    collider = new BoxCollider();
}

void cube::bind() {
    if (this->shader) return;

    /*this->shader = new
            Shader(
            "explosion.vert",
            nullptr, nullptr, "explosion.geom",
            "explosion.frag");*/
    this->shader = new
        Shader(
            "light_texture_color.vert",
            nullptr, nullptr, nullptr,
            "light_texture_color.frag");
    this->shader->Use();
//    this->sf_texture.loadFromFile("../Images/uvtemplate.jpg");
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
//    sf::Texture::bind(&this->sf_texture);
    gpu_obj_t::draw(modelMatrix);
//    sf::Texture::bind(nullptr);

    //gpu_obj_t::draw();
}
