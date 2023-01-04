//
// Created by lkj9487 on 2023/1/4.
//

#include "creeper.h"


creeper_t::creeper_t() {
    this->init();
}

void creeper_t::init() {
    gpu_obj_t::init();

    cube *c = nullptr;

    c = new cube; // Left Front
    c->SettingTransform(pos(0.2, 0.2, 0.4));
    c->SettingScale(sca(0.2,0.2,0.2));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);
    this->LF_feet = c;

    c = new cube; // Left Back
    c->SettingTransform(pos(0.2, 0.2, -0.4));
    c->SettingScale(sca(0.2,0.2,0.2));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);
    this->LB_feet = c;

    c = new cube; // Right Front
    c->SettingTransform(pos(-0.2, 0.2, 0.4));
    c->SettingScale(sca(0.2,0.2,0.2));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);
    this->RF_feet = c;

    c = new cube; // Right Back
    c->SettingTransform(pos(-0.2, 0.2, -0.4));
    c->SettingScale(sca(0.2,0.2,0.2));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);
    this->RB_feet = c;

    c = new cube; // body
    c->SettingTransform(pos(0, 1, 0));
    c->SettingScale(sca(0.4,0.6,0.2));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);

    c = new cube; // Head 8*7
    c->SettingTransform(pos(0, 2, -0.05));
    c->SettingScale(sca(0.4,0.4,0.35));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);

    c = new cube; // Head upper
    c->SettingTransform(pos(0, 2.3, 0.35));
    c->SettingScale(sca(0.4,0.1,0.05));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);

    c = new cube; // near Left eye
    c->SettingTransform(pos(-0.35, 2.1, 0.35));
    c->SettingScale(sca(0.05,0.1,0.05));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);

    c = new cube; // Left eye
    c->SettingTransform(pos(-0.2, 2.1, 0.35));
    c->SettingScale(sca(0.1,0.1,0.05));
    c->SetTexture("../Images/pure_gray.png");
    this->addChildren(c);

    c = new cube; // between eye
    c->SettingTransform(pos(0, 2.1, 0.35));
    c->SettingScale(sca(0.1,0.1,0.05));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);

    c = new cube; // Right eye
    c->SettingTransform(pos(0.2, 2.1, 0.35));
    c->SettingScale(sca(0.1,0.1,0.05));
    c->SetTexture("../Images/pure_gray.png");
    this->addChildren(c);

    c = new cube; // near Right eye
    c->SettingTransform(pos(0.35, 2.1, 0.35));
    c->SettingScale(sca(0.05,0.1,0.05));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);

    c = new cube; // Left face
    c->SettingTransform(pos(-0.3, 1.8, 0.35));
    c->SettingScale(sca(0.1,0.2,0.05));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);

    c = new cube; // Right face
    c->SettingTransform(pos(0.3, 1.8, 0.35));
    c->SettingScale(sca(0.1,0.2,0.05));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);

    c = new cube; // top near Left face
    c->SettingTransform(pos(-0.15, 1.95, 0.35));
    c->SettingScale(sca(0.05,0.05,0.05));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);

    c = new cube; // top near Right face
    c->SettingTransform(pos(0.15, 1.95, 0.35));
    c->SettingScale(sca(0.05,0.05,0.05));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);

    c = new cube; // bottom near Left face
    c->SettingTransform(pos(-0.15, 1.65, 0.35));
    c->SettingScale(sca(0.05,0.05,0.05));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);

    c = new cube; // bottom near Right face
    c->SettingTransform(pos(0.15, 1.65, 0.35));
    c->SettingScale(sca(0.05,0.05,0.05));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);

    c = new cube; // nose
    c->SettingTransform(pos(0, 1.9, 0.35));
    c->SettingScale(sca(0.1,0.1,0.05));
    c->SetTexture("../Images/pure_gray.png");
    this->addChildren(c);

    c = new cube; // Left mouce
    c->SettingTransform(pos(-0.15, 1.8, 0.35));
    c->SettingScale(sca(0.05,0.1,0.05));
    c->SetTexture("../Images/pure_gray.png");
    this->addChildren(c);

    c = new cube; // Right mouce
    c->SettingTransform(pos(0.15, 1.8, 0.35));
    c->SettingScale(sca(0.05,0.1,0.05));
    c->SetTexture("../Images/pure_gray.png");
    this->addChildren(c);

    c = new cube; // under nose
    c->SettingTransform(pos(0, 1.7, 0.35));
    c->SettingScale(sca(0.1,0.1,0.05));
    c->SetTexture("../Images/pure_green.png");
    this->addChildren(c);


}

void creeper_t::bind() {
    if (this->shader) return;
    gpu_obj_t::bind();
}