//
// Created by 林士傑 on 2023/1/2.
//

#ifndef AMUSEMENTPARK_PIECE_H
#define AMUSEMENTPARK_PIECE_H

#include "Object/gpu_object.h"

class Piece : public gpu_obj_t {
    void init() override;

public:
    void bind() override;

    void draw(glm::mat4 modelMatrix = glm::mat4(1)) override;

    Piece();
};


#endif //AMUSEMENTPARK_PIECE_H
