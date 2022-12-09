//
// Created by 林士傑 on 2022/12/6.
//

#include "GameWindow.h"

GameWindow* GameWindow::magic;

GameWindow::GameWindow() {}

GameWindow::GameWindow(const sf::VideoMode &mode, const sf::String &title) : RenderWindow(mode, title, sf::Style::Default, sf::ContextSettings(
        24, // depthBits
        8,  // stencilBits
        4,  // antialiasingLevel
        3,  // majorVersion
        3,   // minorVersion
        sf::ContextSettings::Core
)) {
    GameWindow::magic = this;
    if (!gladLoadGL()) {
        printf("Something went wrong!\n");
        exit(-1);
    }
    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
//    setVerticalSyncEnabled(true);
//    this->setActive(true);

//    arcBall.setup(40, 8, .2, 0, 0);
//    firstPersonCamera.setup(40, 8, .2, 0, 0);

    arcBall.setup(40, 8, 0, 0, 0);
    firstPersonCamera.setup(40, 8, 0, 0, 0);

//    camera = &firstPersonCamera;
    camera = &arcBall;

    gpuObjs.push_back(new cube());

    camera->getEyePosition();
}

void GameWindow::run() {

    for(auto objs : gpuObjs) objs->bind();

    while (isOpen()) {

        sf::Event event;
        while (pollEvent(event)) {

            camera->handle(event);

            if (event.type == sf::Event::Closed)
                close();
        }

        clear();

        glClearStencil(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glEnable(GL_DEPTH);
        glEnable(GL_DEPTH_TEST);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glViewport(0, 0, 800, 600);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        gpu_obj_t::projection_matrix = camera->getPerspectiveMatrix();
        gpu_obj_t::view_matrix = camera->getModelViewMatrix();

        for(auto objs : gpuObjs) objs->draw();

        display();

        for(int i = 0; i < 3; i++){
            cout << camera->getEyePosition()[i] << "";
        }
        cout << "\n";
        for(int i = 0; i < 3; i++){
            cout << camera->getEyeDirection()[i] << "";
        }
        cout << "\n\n";
    }
}
