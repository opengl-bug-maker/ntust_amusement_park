//
// Created by lkj9487 on 2022/12/31.
//
#include "ferwheel_namespace.h"
#include "Object/BasicObject/cube.h"
#include "Object/BasicObject/cylinder.h"
#include "GameWindow.h"
namespace ferwheel {

    car_t::car_t(const char* texture_path, const char* connector_texture_path) {
        this->car_texture_path = texture_path;
        this->connector_texture_path = connector_texture_path;
        init();
    }

    void car_t::init() {
//        srand(time(NULL));

        this->my_rand = (((rand() % 32) - 16.0) / 32.00f);

        gpu_obj_t::init();

        uint8_t tmp_counter = 0;

        this->addChildren(new cylinder); // connector
        this->children[tmp_counter]->SettingTransform(pos(0, -1.768, -0.9));
        this->children[tmp_counter]->SettingRotate(rot(30,0,0));
        this->children[tmp_counter]->collider = nullptr;
        this->children[tmp_counter]->SettingScale(sca(0.05,1.9,0.05));


        ++tmp_counter;
        this->addChildren(new cylinder); // connector
        this->children[tmp_counter]->SettingTransform(pos(0, -1.768, 0.9));
        this->children[tmp_counter]->SettingRotate(rot(330,0,0));
        this->children[tmp_counter]->collider = nullptr;
        this->children[tmp_counter]->SettingScale(sca(0.05,1.9,0.05));

        ++tmp_counter;
        this->addChildren(new cube); // side
        this->children[tmp_counter]->SettingRotate(rot(0,0,0));
        this->children[tmp_counter]->SettingTransform(pos(0,-4.3,1.75));
        this->children[tmp_counter]->SettingScale(sca(1.5,1,0.25));
        this->children[tmp_counter]->collider = nullptr;
        this->children[tmp_counter]->SetTexture(car_texture_path);

        ++tmp_counter;
        this->addChildren(new cube); // side
        this->children[tmp_counter]->SettingRotate(rot(0,0,0));
        this->children[tmp_counter]->SettingTransform(pos(0,-4.3,-1.75));
        this->children[tmp_counter]->SettingScale(sca(1.5,1,0.25));
        this->children[tmp_counter]->collider = nullptr;
        this->children[tmp_counter]->SetTexture(string(this->car_texture_path));

        ++tmp_counter;
        this->addChildren(new cube); // bottom
        this->children[tmp_counter]->SettingRotate(rot(0, 0, 0));
        this->children[tmp_counter]->SettingTransform(pos(0.25,-5.05,0));
        this->children[tmp_counter]->SettingScale(sca(1.25,0.25,1.5));
        this->children[tmp_counter]->SetTexture(string(this->car_texture_path));


        ++tmp_counter;
        this->addChildren(new cube); // go back go back
        this->children[tmp_counter]->SettingRotate(rot(0,0,0));
        this->children[tmp_counter]->SettingTransform(pos(-1.25,-4.3,0));
        this->children[tmp_counter]->SettingScale(sca(0.25,1,1.5));
//        this->children[tmp_counter]->collider = nullptr;
        this->children[tmp_counter]->SetTexture(string(this->car_texture_path));

        ++tmp_counter;
        this->addChildren(new cube); // top bar
        this->children[tmp_counter]->SettingRotate(rot(0,0,0));
        this->children[tmp_counter]->SettingTransform(pos(0,0,0));
        this->children[tmp_counter]->SettingScale(sca(0.5,0.5,3));
        this->children[tmp_counter]->collider = nullptr;
        this->children[tmp_counter]->SetTexture("../Images/purple_metal.png");


        this->start_time = (GLfloat)(GameWindow::magic->nowTime.asSeconds()) + my_rand * 3.14;
    }

    void car_t::bind() {
        if (this->shader) return;
        gpu_obj_t::bind();
    }

    void car_t::draw(glm::mat4 modelMatrix){
        float now_time = (GLfloat)(GameWindow::magic->nowTime.asSeconds());
        this->RotateTo(rot(0,0,(cos((start_time - now_time) * 3) * 5)));
        gpu_obj_t::update();
        gpu_obj_t::draw(modelMatrix);
    }
} // ferwheel::car_t
