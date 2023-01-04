//
// Created by 林士傑 on 2023/1/1.
//

#include "RollerSystem.h"
#include "Object/BasicObject/cube.h"
#include "GameWindow.h"

RailPoint::RailPoint(const glm::vec3 &pos, const glm::vec3 &dir) : pos(pos), dir(dir) {}

RollerSystem::RollerSystem() {
    init();
}

void RollerSystem::init() {
    gpu_obj_t::init();

    gpu_obj_t* car = new locomotive_t();
    car->setName("rollCar");
    addChildren(car);

    SettingRails = vector<RailPoint>();
    SettingRails.emplace_back(glm::vec3(30,0,0), glm::vec3(0,0,0));
    SettingRails.emplace_back(glm::vec3(0,0,30), glm::vec3(0,0,0));
    SettingRails.emplace_back(glm::vec3(-30,0,0), glm::vec3(0,0,0));
    SettingRails.emplace_back(glm::vec3(0,0,-30), glm::vec3(0,0,0));


    float checkPointsCount = 20;
    for (int i = 0; i < SettingRails.size() * checkPointsCount; i++) {
        int now = i / checkPointsCount,
                prev = now - 1 + SettingRails.size(),
                next = now + 1,
                last = now + 2;
        prev %= SettingRails.size();
        next %= SettingRails.size();
        last %= SettingRails.size();
//        float mod = (1 - 1.0f / checkPointsCount) - (i / (float)checkPointsCount - now);
        float mod = i / (float)checkPointsCount - now;
//        glm::vec3 _pos = (
//                                 SettingRails[prev].pos * (mod * mod * mod) +
//                                 SettingRails[now].pos * (1 + 3 * mod + 3 * mod * mod - 3 * mod * mod * mod) +
//                                 SettingRails[next].pos * (4 - 6 * mod * mod + 3 * mod * mod * mod) +
//                                 SettingRails[last].pos * ((1 - mod) * (1 - mod) * (1 - mod))) * (1 / 6.0f);
        glm::vec3 _pos = (
                                 SettingRails[last].pos * (mod * mod * mod) +
                                 SettingRails[next].pos * (1 + 3 * mod + 3 * mod * mod - 3 * mod * mod * mod) +
                                 SettingRails[now].pos * (4 - 6 * mod * mod + 3 * mod * mod * mod) +
                                 SettingRails[prev].pos * ((1 - mod) * (1 - mod) * (1 - mod))) * (1 / 6.0f);
        VirtualRails.emplace_back(_pos,

                                   (SettingRails[prev].dir * (mod * mod * mod) +
                                       SettingRails[now].dir * (1 + 3 * mod + 3 * mod * mod - 3 * mod * mod * mod) +
                                       SettingRails[next].dir * (4 - 6 * mod * mod + 3 * mod * mod * mod) +
                                       SettingRails[last].dir * ((1 - mod) * (1 - mod) * (1 - mod))) * (1 / 6.0f)

        );
    }

    float minLength = 3.0f, maxLength = 4.0f;
//    float minLength = 1.0f, maxLength = 1.3f;
    vector<RailPoint> copy = VirtualRails;
    copy.push_back(copy[0]);
    vector<RailPoint> arcPoints;
    vector<float> PointsLength = vector<float>(copy.size(), 0);
    for (int i = 1; i < copy.size(); i++) {
        PointsLength[i] = PointsLength[i - 1] + glm::length(copy[i].pos - copy[i - 1].pos);
    }
    int ArcPointCount = (PointsLength[copy.size() - 1] / minLength + PointsLength[copy.size() - 1] / maxLength) / 2;
    float ArcLength = PointsLength[copy.size() - 1] / ArcPointCount;
    float TotalArcLength = PointsLength[copy.size() - 1];

    int lastPos = 0;

    for (int i = 0; i < ArcPointCount; i++) {
        float nowLength = ArcLength * i;
        while (nowLength >= PointsLength[lastPos]) {
            lastPos++;
        }
        int prev = lastPos - 1;
        float minus = PointsLength[lastPos] - PointsLength[prev];
        arcPoints.emplace_back(
                copy[prev].pos * ((PointsLength[lastPos] - nowLength) / minus) + copy[lastPos].pos * ((nowLength - PointsLength[prev]) / minus),
                copy[prev].dir * ((PointsLength[lastPos] - nowLength) / minus) + copy[lastPos].dir * ((nowLength - PointsLength[prev]) / minus)
        );
    }

    VirtualRails = arcPoints;

    for(int i = 0; i < VirtualRails.size(); i++){
        gpu_obj_t* c = new cube();
        c->setName("roll " + to_string(i));
        c->SettingTransform(VirtualRails[i].pos);
        c->SettingScale(glm::vec3(0.3f,0.3f,0.3f));
        c->SetTexture("../Images/steel.png");
        addChildren(c);
    }
}

void RollerSystem::bind() {
    if (this->shader) return;

    gpu_obj_t::bind();
}

glm::vec3 RollerSystem::GetTrainPos() {
    float deltaTime = GameWindow::magic->nowTime.asSeconds() - startTime.asSeconds();
    while(deltaTime >= wholeTime){
        deltaTime -= wholeTime;
    }
    float Index = (deltaTime / wholeTime) * (float)VirtualRails.size();
    int startIndex = (int)Index;
    float partial = Index - (float)startIndex;
    return glm::vec3(VirtualRails[startIndex].pos * (1 - partial) + VirtualRails[(startIndex + 1) % VirtualRails.size()].pos * partial);
}

void RollerSystem::Run() {
    startTime = GameWindow::magic->nowTime;
    running = true;
}

void RollerSystem::UpdateTime() {
}

void RollerSystem::GetOut() {
    running = false;
}

void RollerSystem::draw(glm::mat4 modelMatrix) {
    children[0]->MoveTo(GetTrainPos());
    gpu_obj_t::draw(modelMatrix);
}

glm::vec3 RollerSystem::GetTrainDir() {
    float deltaTime = GameWindow::magic->nowTime.asSeconds() - startTime.asSeconds();
    while(deltaTime >= wholeTime){
        deltaTime -= wholeTime;
    }
    float Index = (deltaTime / wholeTime) * (float)VirtualRails.size();
    int startIndex = (int)Index;
    return glm::vec3 (glm::normalize(VirtualRails[(startIndex + 1) % VirtualRails.size()].pos - VirtualRails[startIndex].pos));
}

bool RollerSystem::isRunning() const {
    return running;
}
