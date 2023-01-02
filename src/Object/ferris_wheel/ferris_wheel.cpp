//
// Created by lkj9487 on 2022/12/31.
//
#include "ferris_wheel.h"
#include "Object/BasicObject/cube.h"

ferris_wheel_t::ferris_wheel_t() {
    init();
}

void ferris_wheel_t::init() {
        gpu_obj_t::init();

    cube* c = nullptr;

    c = new cube;
    c->SettingRotate(rot(0,0,330));
    c->Move(pos(-4.9, 8.5, 4.5));
    c->SettingScale(sca(0.5,10,0.5));
    this->addChildren(c);


    c = new cube;
    c->SettingRotate(rot(0,0,30));
    c->Move(pos(4.9, 8.5, 4.5));
    c->SettingScale(sca(0.5,10,0.5));
    this->addChildren(c);

    c = new cube;
    c->SettingRotate(rot(0,0,330));
    c->Move(pos(-4.9, 8.5, -4.5));
    c->SettingScale(sca(0.5,10,0.5));
    this->addChildren(c);

    c = new cube;
    c->SettingRotate(rot(0,0,30));
    c->Move(pos(4.9, 8.5, -4.5));
    c->SettingScale(sca(0.5,10,0.5));
    this->addChildren(c);

    ferwheel::wheel_t* wheel = new ferwheel::wheel_t;
    wheel->setName("wheel");
    wheel->SettingRotate(rot(0,0,0));
    wheel->Move(pos(0,16.8,0));
    wheel->SettingScale(sca(1,1,1));
    this->addChildren(wheel);
    this->my_wheel = wheel;

    this->turn(30);
}

void ferris_wheel_t::bind() {
    if (this->shader) return;
    gpu_obj_t::bind();
}

void ferris_wheel_t::turn(float degree) {
    this->my_wheel->turn(degree);
}

