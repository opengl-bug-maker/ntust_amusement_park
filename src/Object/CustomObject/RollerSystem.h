//
// Created by 林士傑 on 2023/1/1.
//

#ifndef AMUSEMENTPARK_ROLLERSYSTEM_H
#define AMUSEMENTPARK_ROLLERSYSTEM_H

#include "Object/gpu_object.h"
#include "vector"

class RailPoint {
public:
    glm::vec3 pos, dir;

    RailPoint(const glm::vec3 &pos, const glm::vec3 &dir);
};

class RollerSystem : public gpu_obj_t {
    int carCount = 3;
    float wholeTime = 10.0f;
    sf::Time startTime;
    sf::Time nowTime;
    bool running = false;
    void init() override;
    std::vector<RailPoint> SettingRails;
    std::vector<RailPoint> VirtualRails;
public:
    glm::vec3 GetTrainPos();
    glm::vec3 GetTrainDir();
    glm::vec3 GetTrainTop();
    bool isRunning() const;
    void Run();
    void GetOut();
    void UpdateTime();
    void bind() override;

    void draw(glm::mat4 modelMatrix = glm::mat4(1)) override;

    RollerSystem();

};


#endif //AMUSEMENTPARK_ROLLERSYSTEM_H
