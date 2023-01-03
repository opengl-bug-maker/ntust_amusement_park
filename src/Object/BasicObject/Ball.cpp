//
// Created by 林士傑 on 2023/1/3.
//

#include "Ball.h"
#include "GameWindow.h"

Ball::Ball() {
    init();
}

void Ball::init() {
    gpu_obj_t::init();

//    this->model_matrix;
//
    this->vertexCount = 12;
//
    this->data_block_size = {3};
//
    this->data = new float [36]{
            0.000f,  0.000f,  1.000f,
            0.894f,  0.000f,  0.447f,
            0.276f,  0.851f,  0.447f,
            -0.724f,  0.526f,  0.447f,
            -0.724f, -0.526f,  0.447f,
            0.276f, -0.851f,  0.447f,
            0.724f,  0.526f, -0.447f,
            -0.276f,  0.851f, -0.447f,
            -0.894f,  0.000f, -0.447f,
            -0.276f, -0.851f, -0.447f,
            0.724f, -0.526f, -0.447f,
            0.000f,  0.000f, -1.000f
    };
//
    this->vao->element_amount = 20;
//
    element = new GLuint[60] {
            2, 1, 0,
            3, 2, 0,
            4, 3, 0,
            5, 4, 0,
            1, 5, 0,
            11, 6,  7,
            11, 7,  8,
            11, 8,  9,
            11, 9,  10,
            11, 10, 6,
            1, 2, 6,
            2, 3, 7,
            3, 4, 8,
            4, 5, 9,
            5, 1, 10,
            2,  7, 6,
            3,  8, 7,
            4,  9, 8,
            5, 10, 9,
            1, 6, 10
    };
}

void Ball::bind() {
    if (this->shader) return;

    this->shader = new Shader(
            "ball/ball.vert",
            "ball/ball.tesc",
            "ball/ball.tese",
            "ball/ball.geom",
            "ball/ball.frag"
    );

//    this->shader = new
//            Shader(
//            "box.vert",
//            nullptr, nullptr, nullptr,
//            "box.frag");

    this->shader->Use();

    glUniform1f(glGetUniformLocation(this->shader->Program, "TessLevelInner")
                , 3);
    glUniform1f(glGetUniformLocation(this->shader->Program, "TessLevelOuter")
                , 2);

    glUniform3f(glGetUniformLocation(this->shader->Program, "AmbientMaterial")
                , 0.04f, 0.04f, 0.04f);
    glUniform3f(glGetUniformLocation(this->shader->Program, "DiffuseMaterial")
                , 0, 0.75, 0.75);
    float light[3] = {0.25, 0.25, 1};
    glUniform3fv(glGetUniformLocation(this->shader->Program, "LightPosition")
                 , 1, light);
    float packed[9] = { 1, 0, 0,
                        0, 1, 0,
                        0, 0, 1 };

    glm::mat3 nor = glm::transpose(glm::mat3(gpu_obj_t::view_matrix));


    glUniformMatrix3fv(glGetUniformLocation(this->shader->Program, "NormalMatrix")
                       , 1, 0, glm::value_ptr(nor));


    gpu_obj_t::bind();
}

void Ball::draw(glm::mat4 modelMatrix) {
    if(!visible)
        return;
    modelMatrix = modelMatrix * this->model_matrix;
    if(faceToCamera){
        glm::vec3 dir = GetPosition() - GameWindow::magic->firstPersonCamera.getEyePosition();
        dir = glm::normalize(dir);
        glm::vec2 hor = glm::vec2(dir[2], dir[0]);
        hor = glm::normalize(hor);
        double theta = asin(dir[1]);
        double phi = -atan2(hor[1], hor[0]);

        double sp = sin(phi);
        double cp = cos(phi);
        double st = sin(theta);
        double ct = cos(theta);

        glm::mat4 ModelView = glm::mat4(
                cp,  st * sp, -ct * sp, 0,
                0,       ct,       st, 0,
                sp, -st * cp, ct * cp, 0,
                0,        0,       0,1
        );
        modelMatrix = modelMatrix * glm::inverse(ModelView);
    }
    for(auto& child : children){
        child->draw(modelMatrix);
    }
    if(this->shader)
        this->shader->Use();
    else { return; }

    glUniformMatrix4fv(
            glGetUniformLocation(this->shader->Program, "u_projection"), 1, GL_FALSE, glm::value_ptr(gpu_obj_t::projection_matrix));

    glUniformMatrix4fv(
            glGetUniformLocation(this->shader->Program, "u_view"), 1, GL_FALSE, glm::value_ptr(gpu_obj_t::view_matrix));

    glUniformMatrix4fv( //warning : model matrix name
            glGetUniformLocation(this->shader->Program, "u_model"), 1, GL_FALSE, &modelMatrix[0][0]);

    glBindVertexArray(vao->vao);

//    glDrawElements(GL_TRIANGLES, vao->element_amount * 3, GL_UNSIGNED_INT, 0);
//    glPatchParameteri(GL_PATCH_VERTICES, 3);
    glDrawElements(GL_PATCHES, vao->element_amount * 3, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glUseProgram(0);
}

