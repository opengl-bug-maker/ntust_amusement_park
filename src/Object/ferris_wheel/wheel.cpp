//
// Created by lkj9487 on 2022/12/31.
//
#include "ferwheel_namespace.h"
#include "Object/BasicObject/cube.h"
#include "Object/BasicObject/cylinder.h"

namespace ferwheel {

    cube* rows[8];

    double deg2rad(double deg){
        return deg * 0.017453;
    }

    wheel_t::wheel_t() {
        init();
    }

    void wheel_t::init() {
        gpu_obj_t::init();

        for(uint8_t i = 0; i < 4; ++i){
                    
            pos L_pos = pos(9.5f*cos(deg2rad(45*i)), 9.5f*sin(deg2rad(45*i)), 0);
            pos R_pos = pos(9.5f*cos(deg2rad(45*i+180)), 9.5f*sin(deg2rad(45*i+180)), 0);

            cube* c = nullptr;

            c = new cube;
            c->SettingRotate(rot(0,0,45*i));
            c->SettingTransform(pos(0,0,3.5));
            c->SettingScale(sca(10,1,0.5));
            this->addChildren(c);
            c->SetTexture("../Images/purple_metal.png");
            rows[i*2 + 0] = c;

            c = new cube;
            c->SettingRotate(rot(0,0,45*i));
            c->SettingTransform(pos(0,0,-3.5));
            c->SettingScale(sca(10,1,0.5));
            this->addChildren(c);
            c->SetTexture("../Images/purple_metal.png");
            rows[i*2 + 1] = c;


            car_t* car = nullptr;

            car = new car_t("../Images/blue_metal.png", "../Images/blue_metal.png");
            car->setName("carL");
            car->SettingRotate(rot(0,0,0));
            car->SettingTransform(L_pos);
            car->SettingScale(sca(1,1,1));
            this->addChildren(car);

            car = new car_t("../Images/red_metal.jpg", "../Images/red_metal.jpg");
            car->setName("carR");
            car->SettingRotate(rot(0,0,0));
            car->SettingTransform(R_pos);
            car->SettingScale(sca(1,1,1));
            this->addChildren(car);
        }

        cylinder* cyl = new cylinder;
        cyl->SettingRotate(rot(90,0,0));
        cyl->SettingScale(sca(1,5.5,1));
        cyl->SetTexture("../Images/gray.jpg");
        this->addChildren(cyl);
    }

    void wheel_t::bind() {
        if (this->shader) return;
        gpu_obj_t::bind();
    }

    void wheel_t::turn(float degree) {
        degree = fmod(degree, 360);
        cube tmp;
        for(int i = 0; i < 4; i++){

            rows[i*2 + 0]->model_matrix = tmp.model_matrix;
            rows[i*2 + 0]->SettingRotate(rot(0,0,45*i + degree));
            rows[i*2 + 0]->SettingTransform(pos(0,0,3.5));
            rows[i*2 + 0]->SettingScale(sca(10,1,0.5));

            rows[i*2 + 1]->model_matrix = tmp.model_matrix;
            rows[i*2 + 1]->SettingRotate(rot(0,0,45*i + degree));
            rows[i*2 + 1]->SettingTransform(pos(0,0,-3.5));
            rows[i*2 + 1]->SettingScale(sca(10,1,0.5));

            pos L_pos = pos(9.5f*cos(deg2rad(45*i + degree)),
                            9.5f*sin(deg2rad(45*i + degree)), 0);
            pos R_pos = pos(9.5f*cos(deg2rad(45*i + degree + 180)),
                            9.5f*sin(deg2rad(45*i + degree + 180)), 0);


            this->children[i*4 + 2]->MoveTo(L_pos);

            this->children[i*4 + 3]->MoveTo(R_pos);
        }
    }

} // ferwheel::wheel_t