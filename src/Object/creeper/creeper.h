//
// Created by lkj9487 on 2023/1/4.
//

#ifndef AMUSEMENTPARK_CREEPER_H
#define AMUSEMENTPARK_CREEPER_H

#include "gpu_object.h"
#include "Object/BasicObject/cube.h"

class creeper_t : public gpu_obj_t{
    void init() override;

    cube* LB_feet; // Left Back
    cube* LF_feet; // Left Front

    cube* RB_feet; // Right Back
    cube* RF_feet; // Right Front

public:
    void bind() override;
    creeper_t();
};


#endif //AMUSEMENTPARK_CREEPER_H
