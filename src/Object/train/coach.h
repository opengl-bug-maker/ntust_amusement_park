//
// Created by lkj9487 on 2023/1/3.
//

#ifndef AMUSEMENTPARK_COACH_H
#define AMUSEMENTPARK_COACH_H

#include "gpu_object.h"

class coach_t : public gpu_obj_t{
    void init() override;

public:
    void bind() override;
    coach_t();
};


#endif //AMUSEMENTPARK_COACH_H
