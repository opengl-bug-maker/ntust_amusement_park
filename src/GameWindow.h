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
#include "Object/BasicObject/cube.h"
#include "Object/BasicObject/cylinder.h"
#include "Object/BasicObject/Ball.h"
#include "Object/ParticleSystem/Piece.h"
#include "Object/particle.h"
#include "Camera/ArcBallCamera.h"
#include "Camera/Camera.h"
#include "Camera/FirstPersonCamera.h"
#include "Object/Collider/BoxCollider.h"
#include "Object/Collider/BallCollider.h"
#include "Object/CustomObject/player.h"
#include "Object/PhysicsObject.h"
#include "Object/ferris_wheel/ferris_wheel.h"
#include "Object/train/locomotive.h"
#include "Object/train/coach.h"
#include "Object/CustomObject/explosion_test.h"
#include "CustomObject/RollerSystem.h"

class GameWindow : public sf::RenderWindow{
    std::pair<int,int> window_size;
    ArcBallCamera arcBall;
    Camera* camera;
    gpu_obj_t* Player;

    RollerSystem* rs = nullptr;

    std::vector<gpu_obj_t*> gpuObjs;

    sf::Clock deltaClock;
    sf::Time prevTime;
    sf::Time deltaTime;

    void InitObjects();

    void MoveEvent();


public:
    FirstPersonCamera firstPersonCamera;
    static GameWindow* magic;
    static glm::vec3 FallDownVector;
    sf::Time nowTime;

    GameWindow();

    GameWindow(const sf::VideoMode &mode, const sf::String &title);

    void ConsoleEvent(string input);

    void run();
};


#endif //WATEROPENGL_GAMEWINDOW_H
