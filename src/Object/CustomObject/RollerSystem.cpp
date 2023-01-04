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
//    SettingRails.emplace_back(glm::vec3(30,0,0), glm::vec3(0,0,0));
//    SettingRails.emplace_back(glm::vec3(0,0,30), glm::vec3(0,0,0));
//    SettingRails.emplace_back(glm::vec3(-30,0,0), glm::vec3(0,0,0));
//    SettingRails.emplace_back(glm::vec3(0,0,-30), glm::vec3(0,0,0));
    SettingRails.emplace_back(glm::vec3( 24.4376,  4.6053, - 5.5879 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(  8.4258,  4.0960, -45.5349 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(  1.6561, 56.2198, -29.4959 ),glm::vec3(1,0,0));
    SettingRails.emplace_back(glm::vec3( 28.7198, 18.347 , -10.1328 ),glm::vec3(0,0.707107,-0.707107));
    SettingRails.emplace_back(glm::vec3( 31.2873, 18.3991, -32.9051 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3( 18.138 , 17.2923, -31.4484 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(- 0.5373, 14.1773, -26.028  ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(-19.5865, 21.6255, -24.9693 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(-33.773 , 24.181 , -17.865  ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(-37.108 , 22.6669,   2.0535 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(-17.4583, 14.392 ,  10.1164 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(-14.0127, 14.7046, -12.7979 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(-33.3044, 13.4192, -19.252  ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(-37.188 , 12.8637,   1.7739 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(-17.4222,  9.1016,  10.1348 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(-14.0748,  5.9124, -13.0954 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(-32.8957,  5.1773, -19.6089 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(-36.9618,  7.1070,   1.9531 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(-34.6161,  5.7396,  16.2978 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(-25.2172,  5.7298,  26.8965 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3(- 6.3491,  6.5599,  30.1369 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3( 12.771 , 15.5824,  34.0232 ),glm::vec3(-0.573223,0.78033,-0.25));
    SettingRails.emplace_back(glm::vec3(- 5.8817, 42.5551,  28.3654 ),glm::vec3(0,-1,0));
    SettingRails.emplace_back(glm::vec3(-29.2402, 14.3613,  20.3836 ),glm::vec3(1,0,0));
    SettingRails.emplace_back(glm::vec3(- 0.7366,  25.792,  23.7124 ),glm::vec3(0,1,0));
    SettingRails.emplace_back(glm::vec3( 15.6581,  54.71 ,  24.4367 ),glm::vec3(0,0.707107,-0.707107));
    SettingRails.emplace_back(glm::vec3( 24.6502,  38.518,  13.7291 ),glm::vec3(0.707107,0,0.707107));
    SettingRails.emplace_back(glm::vec3( 25.0052, 39.7606, - 2.6705 ),glm::vec3(0.5,-0.5,0.707107));
    SettingRails.emplace_back(glm::vec3( 40.3765, 34.1784,  25.3005 ),glm::vec3(0.5,0.5,-0.707107));
    SettingRails.emplace_back(glm::vec3( 38.959 , 14.3604,  17.3599 ),glm::vec3(0,1,0));




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

//    float minLength = 3.0f, maxLength = 4.0f;
    float minLength = 0.2f, maxLength = 0.3f;
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
        c->SettingScale(glm::vec3(0.1f,0.1f,0.1f));
        c->SetTexture("../Images/steel.png");
        c->collider = nullptr;
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
    glm::vec3 di = GetTrainDir();
    children[0]->RotateTo(glm::vec3(0, atan2(di[2], -di[0]) * 57.2957795147 ,0));
    children[0]->CleanRotate(glm::vec3(0,0, -asin(di[1]) * 57.2957795147));
    children[0]->CleanRotate(glm::vec3(acos(glm::dot(glm::vec3(0,1,0), GetTrainTop())) * 57.2957795147,0, 0));
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

glm::vec3 RollerSystem::GetTrainTop() {
    float deltaTime = GameWindow::magic->nowTime.asSeconds() - startTime.asSeconds();
    while(deltaTime >= wholeTime){
        deltaTime -= wholeTime;
    }
    float Index = (deltaTime / wholeTime) * (float)VirtualRails.size();
    int startIndex = (int)Index;
    float partial = Index - (float)startIndex;
    return glm::vec3(glm::normalize(VirtualRails[startIndex].dir * (1 - partial) + VirtualRails[(startIndex + 1) % VirtualRails.size()].dir * partial));
}

bool RollerSystem::isRunning() const {
    return running;
}
