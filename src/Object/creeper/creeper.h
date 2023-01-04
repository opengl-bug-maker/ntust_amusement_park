//
// Created by lkj9487 on 2023/1/4.
//

#ifndef AMUSEMENTPARK_CREEPER_H
#define AMUSEMENTPARK_CREEPER_H

#include "gpu_object.h"

class creeper_t : public gpu_obj_t{
    void init() override;

    cube* LB_feet; // Left Back
    cube* LF_feet; // Left Front

    cube* RB_feet; // Right Back
    cube* RF_feet; // Right Front

    int32_t start_time = 0;

    int32_t rand_seed;
    float facing_degree;
    float speed;
    sf::Vector2f position = sf::Vector2f(0,0);
    int cnt = 0;

public:
    int my_rand();
    void draw(glm::mat4 modelMatrix) override;
    void bind() override;
    creeper_t();
    void walk();
};


#endif //AMUSEMENTPARK_CREEPER_H
