//
// Created by lkj9487 on 2022/12/31.
//

#include "ferwheel_namespace.h"
#include "ferris_wheel.h"
#include "cube.h"

ferris_wheel_t::ferris_wheel_t() {
    init();
}

void ferris_wheel_t::init() {
    gpu_obj_t::init();

    this->addChildren(new cube);
    this->children[0]->SettingScale(sca(18,1,1));
    this->children[0]->SettingRotate(rot(0,0,120));
    this->children[0]->SettingTransform(pos(28.13, 86.38, 4.5));

    this->addChildren(new cube);
    this->children[1]->SettingScale(pos(18,1,1));
    this->children[1]->SettingRotate(rot(0,0,60));
    this->children[1]->SettingTransform(pos(-28.13, 86.38, 4.5));

    this->addChildren(new cube);
    this->children[2]->SettingScale(pos(18,1,1));
    this->children[2]->SettingRotate(rot(0,0,60));
    this->children[2]->SettingTransform(pos(28.13, 86.38, -4.5));

    this->addChildren(new cube);
    this->children[3]->SettingScale(pos(18,1,1));
    this->children[3]->SettingRotate(rot(0,0,60));
    this->children[3]->SettingTransform(pos(-28.13, 86.38, -4.5));

    this->addChildren(new ferwheel::wheel_t);
    this->children[4]->SettingTransform(pos(0,150,0));
}

void ferris_wheel_t::bind() {
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

void ferris_wheel_t::turn(float degree) {

}

