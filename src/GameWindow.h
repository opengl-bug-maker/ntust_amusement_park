//
// Created by 林士傑 on 2022/12/6.
//

#ifndef WATEROPENGL_GAMEWINDOW_H
#define WATEROPENGL_GAMEWINDOW_H

#pragma once

#include <iostream>
#include <vector>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Object/cube.h"
#include "Utilities/ArcBallCam.H"

class GameWindow : public sf::RenderWindow{
    ArcBallCam arcBall;

    std::vector<gpu_obj_t*> gpuObjs;

public:
    static GameWindow* magic;

    GameWindow();

    GameWindow(const sf::VideoMode &mode, const sf::String &title);

    void run();
};


#endif //WATEROPENGL_GAMEWINDOW_H
