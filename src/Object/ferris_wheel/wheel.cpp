//
// Created by lkj9487 on 2022/12/31.
//
#include "ferwheel_namespace.h"
#include "Object/BasicObject/cube.h"
#include "Object/BasicObject/cylinder.h"

double deg2rad(double deg){
    return deg * 0.017453;
}

namespace ferwheel {

    wheel_t::wheel_t() {
        init();
    }

    void wheel_t::init() {
        gpu_obj_t::init();

        uint8_t tmpcnt = 0;

        for(uint8_t i = 0; i < 4; ++i){
                    
            pos L_pos = pos(9.5f*cos(deg2rad(45*i)), 9.5f*sin(deg2rad(45*i)), 0);
            pos R_pos = pos(9.5f*cos(deg2rad(45*i+180)), 9.5f*sin(deg2rad(45*i+180)), 0);

            uint8_t tmpcnt = 0;

            this->addChildren(new cube);
            this->children[i*4 + tmpcnt]->SettingRotate(rot(0,0,45*i));
            this->children[i*4 + tmpcnt]->SettingTransform(pos(0,0,3.5));
            this->children[i*4 + tmpcnt]->SettingScale(sca(10,1,1));

            tmpcnt++;
            this->addChildren(new cube);
            this->children[i*4 + tmpcnt]->SettingRotate(rot(0,0,45*i));
            this->children[i*4 + tmpcnt]->SettingTransform(pos(0,0,-3.5));
            this->children[i*4 + tmpcnt]->SettingScale(sca(10,1,1));

            tmpcnt++;
            this->addChildren(new car_t);
            this->children[i * 4 + tmpcnt]->setName("carL");
            this->children[i*4 + tmpcnt]->SettingRotate(rot(0,0,0));
            this->children[i*4 + tmpcnt]->SettingTransform(L_pos);
            this->children[i*4 + tmpcnt]->SettingScale(sca(1,1,1));

            tmpcnt++;
            this->addChildren(new car_t);
            this->children[i * 4 + tmpcnt]->setName("carR");
            this->children[i*4 + tmpcnt]->SettingRotate(rot(0,0,0));
            this->children[i*4 + tmpcnt]->SettingTransform(R_pos);
            this->children[i*4 + tmpcnt]->SettingScale(sca(1,1,1));
        }

        this->addChildren(new cylinder);
        this->children[16]->SettingRotate(rot(90,0,0));
        this->children[16]->SettingScale(sca(1,5,1));
    }

    void wheel_t::bind() {
        if (this->shader) return;

        //this->shader = new Shader(
        //    nullptr,
        //    nullptr,
        //    nullptr,
        //    nullptr,
        //    nullptr
        //);
        //this->shader->Use();
        gpu_obj_t::bind();
    }

    void wheel_t::turn(float degree) {
        degree = fmod(degree, 360);
    }

} // ferris_wheel