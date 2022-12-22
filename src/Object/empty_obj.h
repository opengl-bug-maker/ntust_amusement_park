//
// Created by 林士傑 on 2022/12/9.
//

#ifndef WATEROPENGL_EMPTY_H
#define WATEROPENGL_EMPTY_H

#include "gpu_object.h"

class empty_obj : public gpu_obj_t {
    void init() override;

public:
    void bind() override;
    empty_obj();
};


#endif //WATEROPENGL_EMPTY_H
