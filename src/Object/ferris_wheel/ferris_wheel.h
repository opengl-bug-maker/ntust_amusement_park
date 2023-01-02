//
// Created by lkj9487 on 2022/12/31.
//
#pragma once
#ifndef AMUSEMENTPARK_FERRIS_WHEEL_H
#define AMUSEMENTPARK_FERRIS_WHEEL_H

#include "gpu_object.h"
#include "ferwheel_namespace.h"

class ferris_wheel_t : public gpu_obj_t {
    void init() override;
    ferwheel::wheel_t* my_wheel;

public:
    void bind() override;
    ferris_wheel_t();
    void turn(float degree);
};


#endif //AMUSEMENTPARK_FERRIS_WHEEL_H
