//
// Created by lkj9487 on 2022/12/31.
//
#include "ferwheel_namespace.h"

#include "cylinder.h"
#include "cube.h"

namespace ferwheel {
    car_t::car_t() {
        init();
    }

    void car_t::init() {
        gpu_obj_t::init();

        uint8_t tmp_counter = 0;

        this->addChildren(new cylinder); // connector
        this->children[tmp_counter]->SettingScale(sca(0.05,2,0.05));
        this->children[tmp_counter]->SettingRotate(rot(0,0,30));
        this->children[tmp_counter]->SettingTransform(pos(0,-1.768,-1));

        ++tmp_counter;
        this->addChildren(new cylinder); // connector
        this->children[tmp_counter]->SettingScale(sca(0.05,2,0.05));
        this->children[tmp_counter]->SettingRotate(rot(0,0,330));
        this->children[tmp_counter]->SettingTransform(pos(0,-1.768,1));

        ++tmp_counter;
        this->addChildren(new cube); // side
        this->children[tmp_counter]->SettingScale(sca(3,3,0.5));
        this->children[tmp_counter]->SettingRotate(rot(0,0,0));
        this->children[tmp_counter]->SettingTransform(pos(0,-43,1.75));

        ++tmp_counter;
        this->addChildren(new cube); // side
        this->children[tmp_counter]->SettingScale(sca(3,3,0.5));
        this->children[tmp_counter]->SettingRotate(rot(0,0,0));
        this->children[tmp_counter]->SettingTransform(pos(0,-43,-1.75));

        ++tmp_counter;
        this->addChildren(new cube); // bottom
        this->children[tmp_counter]->SettingScale(sca(2.5,0.5,3));
        this->children[tmp_counter]->SettingRotate(rot(0,0,0));
        this->children[tmp_counter]->SettingTransform(pos(2.5,-5,0));

        ++tmp_counter;
        this->addChildren(new cube); // back
        this->children[tmp_counter]->SettingScale(sca(0.5,2,3));
        this->children[tmp_counter]->SettingRotate(rot(0,0,0));
        this->children[tmp_counter]->SettingTransform(pos(-1.25,-43,0));
    }

    void car_t::bind() {
        if (this->shader) return;

        this->shader = new Shader(
            nullptr,
            nullptr,
            nullptr,
            nullptr,
            nullptr
        );

        gpu_obj_t::bind();
    }
} // ferris_wheel