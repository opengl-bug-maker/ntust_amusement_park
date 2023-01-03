//
// Created by 林士傑 on 2023/1/1.
//

#ifndef AMUSEMENTPARK_PARTICLESYSTEM_H
#define AMUSEMENTPARK_PARTICLESYSTEM_H

#include "Object/gpu_object.h"
#include "SpreadSystem.h"

template<typename T>
class ParticleSystem : public gpu_obj_t {
    int maxCount = 50;
    T instance;
    gpu_obj_t* instancePtr;
    vector<gpu_obj_t> particles;

    SpreadSystem spreadSystem;

    void init() override;
public:
    void bind() override;

    void draw(glm::mat4 modelMatrix = glm::mat4(1)) override;

    ParticleSystem();
};


//template<typename T>
//ParticleSystem<T>::ParticleSystem<T>();


#endif //AMUSEMENTPARK_PARTICLESYSTEM_H
