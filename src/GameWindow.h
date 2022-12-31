//
// Created by 林士傑 on 2022/12/6.
//

#ifndef WATEROPENGL_GAMEWINDOW_H
#define WATEROPENGL_GAMEWINDOW_H

#pragma once

#include <iostream>
#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Object/cube.h"
#include "Object/cylinder.h"
#include "Object/particle.h"
#include "Camera/ArcBallCamera.h"
#include "Camera/Camera.h"
#include "Camera/FirstPersonCamera.h"
#include "Object/Collider/BoxCollider.h"
#include "Object/Collider/BallCollider.h"
#include "Object/player.h"
#include "Object/PhysicsObject.h"
#include "Object/ferris_wheel/ferris_wheel.h"
class GameWindow : public sf::RenderWindow{
    ArcBallCamera arcBall;
    FirstPersonCamera firstPersonCamera;
    Camera* camera;
    gpu_obj_t* Player;

    std::vector<gpu_obj_t*> gpuObjs;

    sf::Clock deltaClock;
    sf::Time prevTime;
    sf::Time deltaTime;

    void InitObjects();

    void MoveEvent();


public:
    static GameWindow* magic;
    static glm::vec3 FallDownVector;
    sf::Time nowTime;

    GameWindow();

    GameWindow(const sf::VideoMode &mode, const sf::String &title);

    void run();
};


#endif //WATEROPENGL_GAMEWINDOW_H
