//
// Created by 林士傑 on 2022/12/7.
//

#ifndef WATEROPENGL_CUBE_H
#define WATEROPENGL_CUBE_H

#include "gpu_object.h"
#include "Object/Collider/BoxCollider.h"
#include "ferris_wheel/ferwheel_namespace.h"

class cube : public gpu_obj_t {
    friend ferwheel::wheel_t;
    void init() override;

public:
    void bind() override;
    void draw(glm::mat4 modelMatrix = glm::mat4(1)) override;
    cube();
};


#endif //WATEROPENGL_CUBE_H
