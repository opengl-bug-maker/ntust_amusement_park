//
// Created by lkj9487 on 2022/12/31.
//

#pragma once
#ifndef AMUSEMENTPARK_FERWHEEL_NAMESPACE_H
#define AMUSEMENTPARK_FERWHEEL_NAMESPACE_H

#include "gpu_object.h"

using pos=glm::vec3; // position
using sca=glm::vec3; // scale
using rot=glm::vec3; // rotate

namespace ferwheel {

    double deg2rad(double deg);

    class car_t : public gpu_obj_t {
        float my_rand;
        float start_time;
        void init() override;
        void draw(glm::mat4 modelMatrix) override;
        const char* car_texture_path;
        const char* connector_texture_path;

    public:
        void bind() override;
        car_t(const char*, const char*);
    };

    class wheel_t : public gpu_obj_t {
        void init() override;
//        cube* rows[8];
    public:
        void bind() override;
        wheel_t();
        void turn(float degree);
    };

}

#endif //AMUSEMENTPARK_FERWHEEL_NAMESPACE_H
