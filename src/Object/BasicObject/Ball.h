//
// Created by 林士傑 on 2023/1/3.
//

#ifndef AMUSEMENTPARK_BALL_H
#define AMUSEMENTPARK_BALL_H

#include "gpu_object.h"

class Ball : public gpu_obj_t {
    void init() override;

public:
    void bind() override;
    void draw(glm::mat4 modelMatrix) override;
    glm::vec4 color;
    Ball();

};


#endif //AMUSEMENTPARK_BALL_H
