//
// Created by lkj9487 on 2023/1/4.
//

#include "creeper.h"
#include "GameWindow.h"

#include "Object/BasicObject/cube.h"

creeper_t::creeper_t() {
    this->init();
}

void creeper_t::init() {
    gpu_obj_t::init();

    this->start_time = (GLfloat)(GameWindow::magic->nowTime.asMilliseconds());

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

    this->rand_seed = time(NULL);
}

void creeper_t::bind() {
    if (this->shader) return;
    gpu_obj_t::bind();
}

int creeper_t::my_rand() {
    return (((rand_seed * 5) ^ rand() ^ rand()) % 100);
}

void creeper_t::draw(glm::mat4 modelMatrix) {
    int32_t now_time = (int32_t)(GameWindow::magic->nowTime.asMilliseconds());

    if((now_time - this->start_time) % 1000 > 25){
        this->start_time = now_time;
        walk();
    }
    gpu_obj_t::update();
    gpu_obj_t::draw(modelMatrix);
}

void creeper_t::walk() {

    float delta_degree = 0.0f;

    cnt++;

    if(cnt > 50){
        delta_degree = ((fabs(fmod(float(my_rand()), 4.0f)) - 2.0f));
        cnt = 0;
    }

    speed = fabs(float((my_rand() % 5) + 1) / 100.0f) * 4;

    float new_facing = 0;
    sf::Vector2f new_pos(0,0);

    new_facing = facing_degree + delta_degree;

    new_pos.x = position.x + speed * std::cos(glm::radians(float(new_facing))); // x is x in window
    new_pos.y = position.y - speed * std::sin(glm::radians(float(new_facing))); // y is z in window

    while(true){
        if(new_pos.x >= 10){
            int rand_deg = my_rand() % 135 + 136;
            delta_degree = rand_deg - facing_degree;
            new_facing = rand_deg;
            new_pos.x = position.x + speed * std::cos(glm::radians(float(new_facing))); // x is x in window
            new_pos.y = position.y - speed * std::sin(glm::radians(float(new_facing))); // y is z in window
        }
        else if(new_pos.x <= -10){
            int rand_deg = my_rand() % 135 + 316;
            delta_degree = rand_deg - facing_degree;
            new_facing = rand_deg;
            new_pos.x = position.x + speed * std::cos(glm::radians(float(new_facing))); // x is x in window
            new_pos.y = position.y - speed * std::sin(glm::radians(float(new_facing))); // y is z in window
        }
        else if(new_pos.y >= 10){
            int rand_deg = my_rand() % 135 + 46;
            delta_degree = rand_deg - facing_degree;
            new_facing = rand_deg;
            new_pos.x = position.x + speed * std::cos(glm::radians(float(new_facing))); // x is x in window
            new_pos.y = position.y - speed * std::sin(glm::radians(float(new_facing))); // y is z in window
        }
        else if(new_pos.y <= -10){
            int rand_deg = my_rand() % 135 + 226;
            delta_degree = rand_deg - facing_degree;
            new_facing = rand_deg;
            new_pos.x = position.x + speed * std::cos(glm::radians(float(new_facing))); // x is x in window
            new_pos.y = position.y - speed * std::sin(glm::radians(float(new_facing))); // y is z in window
        }else{
            break;
        }
    }

    position = new_pos;

    if(new_facing < 0){
        new_facing = 360 + new_facing;
    }

    facing_degree = std::fmod(new_facing,360.0f);

    if (delta_degree < 0){
        delta_degree = 360 + delta_degree;
    }

    delta_degree = std::fmod(delta_degree, 360.0f);

    this->SettingRotate(rot(0,delta_degree,0));
    this->SettingTransform(pos(0,0,speed));

    static uint32_t theta = 90;
    static bool flag = true;
    const int delta_feet = 2;
    if(flag){
        theta = theta + delta_feet;
        if(theta > 119){ flag = false; }
    }else{
        theta = theta - delta_feet;
        if(theta < 61){ flag = true; }
    }
    LF_feet->SettingRotate(rot((flag ? delta_feet : 360 - delta_feet),0,0));
    LB_feet->SettingRotate(rot((flag ? 360 - delta_feet : delta_feet),0,0));
    RF_feet->SettingRotate(rot((flag ? 360 - delta_feet : delta_feet),0,0));
    RB_feet->SettingRotate(rot((flag ? delta_feet : 360 - delta_feet),0,0));

}

