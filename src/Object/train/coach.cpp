//
// Created by lkj9487 on 2023/1/3.
//
#include "train_namespace.h"
#include "coach.h"

#include "BasicObject/cube.h"
#include "BasicObject/cylinder.h"

coach_t::coach_t() {
    this->init();
}

void coach_t::init() {
    gpu_obj_t::init();

    cylinder *cyl = nullptr;
    cube *c = nullptr;

    cyl = new cylinder; // Left wheel 0
    cyl->SettingTransform(train_ns::train_pos(-0.8, 0.3, 0.85));
    cyl->SettingRotate(rot(90,0,0));
    cyl->SettingScale(sca(0.3,0.05,0.3));
    cyl->SetTexture("../Images/train_wheel.png");
    this->addChildren(cyl);

    cyl = new cylinder; // Left wheel 1
    cyl->SettingTransform(train_ns::train_pos(0.8, 0.3, 0.85));
    cyl->SettingRotate(rot(90,0,0));
    cyl->SettingScale(sca(0.3,0.05,0.3));
    cyl->SetTexture("../Images/train_wheel.png");
    this->addChildren(cyl);

    cyl = new cylinder; // Right wheel 0
    cyl->SettingTransform(train_ns::train_pos(-0.8, 0.3, -0.85));
    cyl->SettingRotate(rot(90,0,0));
    cyl->SettingScale(sca(0.3,0.05,0.3));
    cyl->SetTexture("../Images/train_wheel.png");
    this->addChildren(cyl);

    cyl = new cylinder; // Right wheel 1
    cyl->SettingTransform(train_ns::train_pos(0.8, 0.3, -0.85));
    cyl->SettingRotate(rot(90,0,0));
    cyl->SettingScale(sca(0.3,0.05,0.3));
    cyl->SetTexture("../Images/train_wheel.png");
    this->addChildren(cyl);

    c = new cube; // bottom
    c->SettingTransform(train_ns::train_pos(0, 0.5, 0));
    c->SettingScale(sca(1.2, 0.1, 0.6));
    c->SetTexture("../Images/coach.png");
    this->addChildren(c);

    c = new cube; // front
    c->SettingTransform(train_ns::train_pos(-1.3, 0.9, 0));
    c->SettingScale(sca(0.1, 0.5, 0.6));
    c->SetTexture("../Images/coach.png");
    this->addChildren(c);

    c = new cube; // back
    c->SettingTransform(train_ns::train_pos(1.3, 0.9, 0));
    c->SettingScale(sca(0.1, 0.5, 0.6));
    c->SetTexture("../Images/coach.png");
    this->addChildren(c);

    c = new cube; // left
    c->SettingTransform(train_ns::train_pos(0, 0.9, 0.7));
    c->SettingScale(sca(1.4, 0.5, 0.1));
    c->SetTexture("../Images/coach.png");
    this->addChildren(c);

    c = new cube; // right
    c->SettingTransform(train_ns::train_pos(0, 0.9, -0.7));
    c->SettingScale(sca(1.4, 0.5, 0.1));
    c->SetTexture("../Images/coach.png");
    this->addChildren(c);
}

void coach_t::bind() {
    if (this->shader) return;
    gpu_obj_t::bind();
}