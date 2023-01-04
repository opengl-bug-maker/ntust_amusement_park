//
// Created by lkj9487 on 2023/1/2.
//
//#pragma once
#ifndef AMUSEMENTPARK_TRAIN_NAMESPACE_H
#define AMUSEMENTPARK_TRAIN_NAMESPACE_H

#include "gpu_object.h"

//using pos=glm::vec3; // position
using sca=glm::vec3; // scale
using rot=glm::vec3; // rotate

namespace train_ns {

    inline glm::vec3 train_pos(float a, float b, float c) {
        return glm::vec3(a, b, c);
    }

    double deg2rad(double deg);

    class wheel : public gpu_obj_t {
        void init() override;

    public:
        void bind() override;
        wheel();
    };
}


#endif //AMUSEMENTPARK_TRAIN_NAMESPACE_H
