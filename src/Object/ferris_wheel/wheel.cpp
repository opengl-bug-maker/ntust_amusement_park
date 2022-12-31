//
// Created by lkj9487 on 2022/12/31.
//
#include "ferwheel_namespace.h"
#include "cube.h"
#include "cylinder.h"

double deg2rad(double deg){
    return deg * 0.017453;
}

namespace ferwheel {

    wheel_t::wheel_t() {
        init();
    }

    void wheel_t::init() {
        gpu_obj_t::init();

        for(uint8_t i; i < 4; ++i){

            pos L_pos = pos(cos(9.5f*deg2rad(45*i)), 9.5f*sin(deg2rad(45*i)), 0);
            pos R_pos = pos(cos(9.5f*deg2rad(45*i+180)), 9.5f*sin(deg2rad(45*i+180)), 0);

            uint8_t tmpcnt = 0;

            this->addChildren(new cube);
            this->children[i*6 + tmpcnt]->SettingScale(sca(20,2,2));
            this->children[i*6 + tmpcnt]->SettingRotate(rot(0,0,45*i));
            this->children[i*6 + tmpcnt]->SettingTransform(pos(0,0,3.5));

            tmpcnt++;
            this->addChildren(new cube);
            this->children[i*6 + tmpcnt]->SettingScale(sca(20,2,2));
            this->children[i*6 + tmpcnt]->SettingRotate(rot(0,0,45*i));
            this->children[i*6 + tmpcnt]->SettingTransform(pos(0,0,-3.5));

            tmpcnt++;
            this->addChildren(new car_t);
            this->children[i*6 + tmpcnt]->SettingScale(sca(1,1,1));
            this->children[i*6 + tmpcnt]->SettingRotate(rot(0,0,0));
            this->children[i*6 + tmpcnt]->SettingTransform(L_pos);

            tmpcnt++;
            this->addChildren(new cube);
            this->children[i*6 + tmpcnt]->SettingScale(sca(1,1,6));
            this->children[i*6 + tmpcnt]->SettingRotate(rot(0,0,0));
            this->children[i*6 + tmpcnt]->SettingTransform(L_pos);

            tmpcnt++;
            this->addChildren(new car_t);
            this->children[i*6 + tmpcnt]->SettingScale(sca(1,1,1));
            this->children[i*6 + tmpcnt]->SettingRotate(rot(0,0,0));
            this->children[i*6 + tmpcnt]->SettingTransform(R_pos);

            tmpcnt++;
            this->addChildren(new cube);
            this->children[i*6 + tmpcnt]->SettingScale(sca(1,1,6));
            this->children[i*6 + tmpcnt]->SettingRotate(rot(0,0,0));
            this->children[i*6 + tmpcnt]->SettingTransform(R_pos);
        }

        this->addChildren(new cylinder);
        this->children[24]->SettingScale(sca(2, 5,2));
        this->children[24]->SettingRotate(rot(90,0,0));
    }

    void wheel_t::bind() {
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

    void wheel_t::turn(float degree) {
        degree = fmod(degree, 360);
    }

} // ferris_wheel