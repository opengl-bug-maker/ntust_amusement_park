//
// Created by lkj9487 on 2023/1/2.
//
#pragma once
#ifndef AMUSEMENTPARK_LOCOMOTIVE_H
#define AMUSEMENTPARK_LOCOMOTIVE_H

//#include "train_namespace.h"
#include "gpu_object.h"

class locomotive_t : public gpu_obj_t{
    void init() override;

public:
    void bind() override;
    locomotive_t();
};


#endif //AMUSEMENTPARK_LOCOMOTIVE_H
