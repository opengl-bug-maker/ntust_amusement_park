//
// Created by 林士傑 on 2022/12/7.
//

#ifndef WATEROPENGL_CUBE_H
#define WATEROPENGL_CUBE_H

#include "gpu_object.h"

class cube : public gpu_obj_t {
    void init() override;

public:
    void bind() override;
    cube();
    cube(GLfloat* input_data);
};


#endif //WATEROPENGL_CUBE_H
