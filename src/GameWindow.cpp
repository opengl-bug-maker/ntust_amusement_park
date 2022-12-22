//
// Created by 林士傑 on 2022/12/6.
//

#include "GameWindow.h"
#include "Object/gpu_object.h"

GameWindow* GameWindow::magic;
glm::vec3 GameWindow::FallDownVector = glm::vec3(0, -1, 0);

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
//region glSetting
    if (!gladLoadGL()) {
        printf("Something went wrong!\n");
        exit(-1);
    }
    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
//    setVerticalSyncEnabled(true);
//    this->setActive(true);
//endregion

//region setting
    prevTime = deltaClock.getElapsedTime();

    arcBall.setup(40, 8, 0, 0, 0);
    firstPersonCamera.setup(40, 8, 0, 0, 0);
    firstPersonCamera.lock();

    camera = &firstPersonCamera;
//    camera = &arcBall;
//endregion

//region object

    gpu_obj_t* cc = new cube();

    gpu_obj_t* c = new cube();
    c->Translate(glm::vec3(3, 0, 0));
    c->Scale(glm::vec3(0.5, 0.5, 0.5));
    cc->addChildren(c);
    c = new cube();
    c->Translate(glm::vec3(0, 3, 0));
    c->Scale(glm::vec3(0.5, 0.5, 0.5));
    cc->addChildren(c);
    c = new cube();
    c->Translate(glm::vec3(0, 0, 3));
    c->Scale(glm::vec3(0.5, 0.5, 0.5));
    cc->addChildren(c);

    gpuObjs.push_back(cc);
//endregion

}

void GameWindow::run() {

    firstPersonCamera.lock();

    for(auto objs : gpuObjs) objs->bind();

    while (isOpen()) {
        nowTime = deltaClock.getElapsedTime();
        deltaTime = nowTime - prevTime;

        for(auto objs : gpuObjs) objs->FallDown(deltaTime);

        for(auto objs : gpuObjs) objs->UpdatePosition(deltaTime);

        sf::Event event;
        while (pollEvent(event)) {

            camera->handle(event);

            if (event.type == sf::Event::Closed)
                close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1){
                camera = (camera == &firstPersonCamera) ? ((Camera*)&arcBall) : ((Camera*)&firstPersonCamera);
            }
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


//        glm::vec3 dire = camera->getEyeDirection();
//        for (int i = 0; i < 3; ++i) {
//            cout << dire[i] << " ";
//        }
//        cout << "\n";
//        for (int i = 0; i < 3; ++i) {
//            dire[i] *= 8;
//        }

//        gpuObjs[1]->SetPosition(dire + camera->getEyePosition());

//        glm::mat4 viewmatrix = camera->getModelViewMatrix();
//        for (int i = 0; i < 4; ++i) {
//            for (int j = 0; j < 4; ++j) {
//                cout << viewmatrix[i][j] << " ";
//            }
//            cout << "\n";
//        }
//        cout << "\n";
//        cout << "\n";

        prevTime = nowTime;
    }
}
