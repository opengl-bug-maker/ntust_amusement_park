//
// Created by lkj9487 on 2022/12/31.
//
#include "ferwheel_namespace.h"

#include "Object/BasicObject/cylinder.h"
#include "Object/BasicObject/cube.h"

namespace ferwheel {
    car_t::car_t() {
        init();
    }

    void car_t::init() {
        gpu_obj_t::init();

        uint8_t tmp_counter = 0;

        this->addChildren(new cylinder); // connector
        this->children[tmp_counter]->SettingTransform(pos(0, -1.768, -0.9));
        this->children[tmp_counter]->SettingRotate(rot(30,0,0));
        this->children[tmp_counter]->SettingScale(sca(0.05,1.9,0.05));

        ++tmp_counter;
        this->addChildren(new cylinder); // connector
        this->children[tmp_counter]->SettingTransform(pos(0, -1.768, 0.9));
        this->children[tmp_counter]->SettingRotate(rot(330,0,0));
        this->children[tmp_counter]->SettingScale(sca(0.05,1.9,0.05));
        
        ++tmp_counter;
        this->addChildren(new cube); // side
        this->children[tmp_counter]->SettingRotate(rot(0,0,0));
        this->children[tmp_counter]->SettingTransform(pos(0,-4.3,1.75));
        this->children[tmp_counter]->SettingScale(sca(1.5,1,0.25));

        ++tmp_counter;
        this->addChildren(new cube); // side
        this->children[tmp_counter]->SettingRotate(rot(0,0,0));
        this->children[tmp_counter]->SettingTransform(pos(0,-4.3,-1.75));
        this->children[tmp_counter]->SettingScale(sca(1.5,1,0.25));

        ++tmp_counter;
        this->addChildren(new cube); // bottom
        this->children[tmp_counter]->SettingRotate(rot(0, 0, 0));
        this->children[tmp_counter]->SettingTransform(pos(0.25,-5.05,0));
        this->children[tmp_counter]->SettingScale(sca(1.25,0.25,1.5));

        ++tmp_counter;
        this->addChildren(new cube); // back
        this->children[tmp_counter]->SettingRotate(rot(0,0,0));
        this->children[tmp_counter]->SettingTransform(pos(-1.25,-4.3,0));
        this->children[tmp_counter]->SettingScale(sca(0.25,1,1.5));

        ++tmp_counter;
        this->addChildren(new cube); // top bar
        this->children[tmp_counter]->SettingRotate(rot(0,0,0));
        this->children[tmp_counter]->SettingTransform(pos(0,0,0));
        this->children[tmp_counter]->SettingScale(sca(0.5,0.5,3));
    }

    void car_t::bind() {
        if (this->shader) return;

   /*     this->shader = new Shader(
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr
        );*/
        //this->shader->Use();
        gpu_obj_t::bind();

    }
} // ferris_wheel