//
// Created by lkj9487 on 2023/1/2.
//

#include "train_namespace.h"
#include "locomotive.h"

#include "BasicObject/Ball.h"
#include "BasicObject/cube.h"
#include "BasicObject/cylinder.h"

locomotive_t::locomotive_t() {
    this->init();
}

void locomotive_t::init() {
    gpu_obj_t::init();

    cylinder* cyl = nullptr;
    cube* c = nullptr;
    Ball* ball = nullptr;

    cyl = new cylinder; // Left wheel 0
    cyl->SettingTransform(train_ns::train_pos(-1.4, 0.3, 0.85));
    cyl->SettingRotate(rot(90,0,0));
    cyl->SettingScale(sca(0.3,0.05,0.3));
    this->addChildren(cyl);

    cyl = new cylinder; // Left wheel 1
    cyl->SettingTransform(train_ns::train_pos(0.3, 0.3, 0.85));
    cyl->SettingRotate(rot(90,0,0));
    cyl->SettingScale(sca(0.3,0.05,0.3));
    this->addChildren(cyl);

    cyl = new cylinder; // Left wheel 2
    cyl->SettingTransform(train_ns::train_pos(0.95, 0.3, 0.85));
    cyl->SettingRotate(rot(90,0,0));
    cyl->SettingScale(sca(0.3,0.05,0.3));
    this->addChildren(cyl);

    cyl = new cylinder; // Left wheel 3
    cyl->SettingTransform(train_ns::train_pos(1.6, 0.3, 0.85));
    cyl->SettingRotate(rot(90,0,0));
    cyl->SettingScale(sca(0.3,0.05,0.3));
    this->addChildren(cyl);

    cyl = new cylinder; // Right wheel 0
    cyl->SettingTransform(train_ns::train_pos(-1.4, 0.3, -0.85));
    cyl->SettingRotate(rot(90,0,0));
    cyl->SettingScale(sca(0.3,0.05,0.3));
    this->addChildren(cyl);

    cyl = new cylinder; // Right wheel 1
    cyl->SettingTransform(train_ns::train_pos(0.3, 0.3, -0.85));
    cyl->SettingRotate(rot(90,0,0));
    cyl->SettingScale(sca(0.3,0.05,0.3));
    this->addChildren(cyl);

    cyl = new cylinder; // Right wheel 2
    cyl->SettingTransform(train_ns::train_pos(0.95, 0.3, -0.85));
    cyl->SettingRotate(rot(90,0,0));
    cyl->SettingScale(sca(0.3,0.05,0.3));
    this->addChildren(cyl);

    cyl = new cylinder; // Right wheel 3
    cyl->SettingTransform(train_ns::train_pos(1.6, 0.3, -0.85));
    cyl->SettingRotate(rot(90,0,0));
    cyl->SettingScale(sca(0.3,0.05,0.3));
    this->addChildren(cyl);


    c = new cube; // bottom
    c->SettingTransform(train_ns::train_pos(0, 0.5, 0));
    c->SettingScale(sca(1.8, 0.1, 0.8));
    this->addChildren(c);

    cyl = new cylinder; // boiler
    cyl->SettingTransform(train_ns::train_pos(-0.725, 1.2, 0));
    cyl->SettingRotate(rot(0,0,90));
    cyl->SettingScale(sca(0.6,0.925,0.6));
    this->addChildren(cyl);

    cyl = new cylinder; // chimney of boiler
    cyl->SettingTransform(train_ns::train_pos(-1.3, 2, 0));
    cyl->SettingRotate(rot(0,0,0));
    cyl->SettingScale(sca(0.3,0.5,0.3));
    this->addChildren(cyl);

//
//    ball = new Ball; // boiler
//    ball->MoveTo(train_ns::train_pos(0,8,0));
//    ball->SettingScale(sca(1.2,1.2,1.2));
//    ball->SetGravity(false);
//    this->addChildren(ball);

    // driver room
    c = new cube;
    c->SettingTransform(train_ns::train_pos(0.3, 1.475, 0.7));
    c->SettingScale(sca(0.1,0.875,0.1));
    this->addChildren(c);
    c = new cube;
    c->SettingTransform(train_ns::train_pos(0.3, 1.475, -0.7));
    c->SettingScale(sca(0.1,0.875,0.1));
    this->addChildren(c);
    c = new cube;
    c->SettingTransform(train_ns::train_pos(1.7, 1.475, 0.7));
    c->SettingScale(sca(0.1,0.875,0.1));
    this->addChildren(c);
    c = new cube;
    c->SettingTransform(train_ns::train_pos(1.7, 1.475, -0.7));
    c->SettingScale(sca(0.1,0.875,0.1));
    this->addChildren(c);
    c = new cube;
    c->SettingTransform(train_ns::train_pos(1, 1, 0.7));
    c->SettingScale(sca(0.6,0.4,0.1));
    this->addChildren(c);
    c = new cube;
    c->SettingTransform(train_ns::train_pos(1, 1, -0.7));
    c->SettingScale(sca(0.6,0.4,0.1));
    this->addChildren(c);
    c = new cube;
    c->SettingTransform(train_ns::train_pos(1.7, 1, 0));
    c->SettingScale(sca(0.1,0.4,0.6));
    this->addChildren(c);
    c = new cube;
    c->SettingTransform(train_ns::train_pos(0.3, 1.2, 0));
    c->SettingScale(sca(0.1,0.6,0.6));
    this->addChildren(c);
    c = new cube;
    c->SettingTransform(train_ns::train_pos(0.825, 2.45, 0));
    c->SettingScale(sca(0.975,0.1,0.8));
    this->addChildren(c);

}

void locomotive_t::bind() {
    if (this->shader) return;
    gpu_obj_t::bind();
}