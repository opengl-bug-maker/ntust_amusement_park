//
// Created by ªL¤h³Ç on 2022/12/9.
//

#ifndef WATEROPENGL_EMPTY_H
#define WATEROPENGL_EMPTY_H

#include "gpu_object.h"
#include "Object/Collider/BoxCollider.h"
class cylinder : public gpu_obj_t {
    void init() override;

public:
    void bind() override;
    void draw(glm::mat4 modelMatrix = glm::mat4(1)) override;
    cylinder();
    
};


#endif //WATEROPENGL_EMPTY_H
