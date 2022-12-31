//
// Created by lkj9487 on 2022/12/31.
//

#ifndef AMUSEMENTPARK_FERWHEEL_NAMESPACE_H
#define AMUSEMENTPARK_FERWHEEL_NAMESPACE_H

#include "gpu_object.h"

using pos=glm::vec3; // position
using sca=glm::vec3; // scale
using rot=glm::vec3; // rotate

namespace ferwheel {
    class car_t : public gpu_obj_t {
        void init() override;

    public:
        void bind() override;
        car_t();
    };

    class wheel_t : public gpu_obj_t {
        void init() override;

    public:
        void bind() override;
        wheel_t();
        void turn(float degree);
    };
//    extern class wheel_t;
}

#endif //AMUSEMENTPARK_FERWHEEL_NAMESPACE_H
