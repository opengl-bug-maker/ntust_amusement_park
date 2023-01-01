//
// Created by 林士傑 on 2022/12/6.
//

#include "GameWindow.h"
//#include "Object/ferris_wheel/ferwheel_namespace.h"

//#include "Object/gpu_object.h"

GameWindow* GameWindow::magic;
glm::vec3 GameWindow::FallDownVector = glm::vec3(0, -20, 0);

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
    setVerticalSyncEnabled(true);
//    this->setActive(true);
//endregion

//region setting
    prevTime = deltaClock.getElapsedTime();

    arcBall.setup(40, 8, 0, 0, 0);
    firstPersonCamera.setup(60, 8, 0, 0, 0);
    firstPersonCamera.lock();

    camera = &firstPersonCamera;
//    camera = &arcBall;
//endregion

    InitObjects();
}

void GameWindow::InitObjects() {
//region object
    Player = new player();
    Player->setName("player");
//    Player = new cube();
//    Player->SetGravity(false);
    Player->SettingTransform(glm::vec3(0, 0, 8));
    Player->SettingScale(glm::vec3(1, 2, 1));
//    Player->SettingTransform(glm::vec3(0, 10, 0));
    gpuObjs.push_back(Player);

    gpu_obj_t* plane = new cube();
    plane->setName("plane");
    plane->SettingTransform(glm::vec3(0, -10, 0));
    plane->SettingScale(glm::vec3(10, 0.1, 10));
    plane->SetGravity(false);
    gpuObjs.push_back(plane);


    //gpu_obj_t* cc = new cube();
    //cc->setName("big cube");
//    cc->SetGravity(false);
//    cc->SettingScale(glm::vec3(0.2,0.2,0.2));

     gpu_obj_t* c = new cube();
    /*c->setName("x cube");
    c->SettingTransform(glm::vec3(3, 0, 0));
    c->SettingScale(glm::vec3(0.5, 0.5, 0.5));
    c->SetGravity(false);
    gpuObjs.push_back(c);*/
    //cc->addChildren(c);
// 
// 
      //c = new explosion_test_t();
      //  c->setName("z cube");
      //  c->SettingTransform(glm::vec3(0, 0, 3));
      //  c->SettingScale(glm::vec3(0.5, 0.5, 0.5));
      //  c->SetGravity(false);
      //  gpuObjs.push_back(c);

    //c = new cylinder();
    //c->setName("cylinder 0");
    //c->SettingScale(glm::vec3(2, 2, 0.5));
    //c->SettingTransform(glm::vec3(0, 0, 100));
    //c->SettingRotate(glm::vec3(90,0,0));
    //    c->SetGravity(false);
    //gpuObjs.push_back(c);
    //    cc->addChildren(c);

    //c = new particle_t();
    //c->setName("particle 0");
    //c->SettingTransform(glm::vec3(0, 2, 5));
    //c->SettingScale(glm::vec3(1, 1, 1));
    //c->SetGravity(false);
    //gpuObjs.push_back(c);
        //cc->addChildren(c);

    c = new ferris_wheel_t;
    c->setName("ferris_wheel 0");
    c->SettingTransform(glm::vec3(0, 0, 0));
    c->SettingScale(glm::vec3(1,1,1));
    c->SetGravity(false);
    gpuObjs.push_back(c);

    //gpuObjs.push_back(cc);
//endregion
}

void GameWindow::run() {
    for(auto objs : gpuObjs) objs->bind();
    //sf::Texture texture1;
    //
    //texture1.loadFromFile("X:/CS/2022ComputerGraphics/Projects/ntust_amusement_park/Images/uvtemplate.jpg");

    
    
    while (isOpen()) {
        nowTime = deltaClock.getElapsedTime();
        deltaTime = nowTime - prevTime;

        for(auto objs : gpuObjs) objs->nextTick();

        MoveEvent();

        for(auto objs : gpuObjs) objs->FallDown(deltaTime);

        glm::vec3 collisionVec;

        for(int i = 0; i < gpuObjs.size(); i++){
            for(int j = 0; j < gpuObjs.size(); j++){
                if(gpuObjs[i]->IsCollision(gpuObjs[j], collisionVec)){
                    if(glm::length(collisionVec) > 0.1)
                        gpuObjs[i]->Move(collisionVec);
                    glm::vec3 coll = glm::normalize(collisionVec);
                    if(glm::abs(glm::length(coll)) > 0.000000001)
                        gpuObjs[i]->addVelocity(coll * (-glm::dot(gpuObjs[i]->getVelocity(), coll)));
                }
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && ((player*)Player)->state == player::ActionState::Floor){
            cout << "jump" << endl;
            ((player*)Player)->state = player::ActionState::Drop;
            glm::vec3 jump = glm::vec3 (0, 10, 0);
            jump[0] = Player->getVelocity()[0];
            jump[2] = Player->getVelocity()[2];
            Player->setVelocity(jump);
        }


        for(auto objs : gpuObjs) objs->UpdatePosition(deltaTime);

        firstPersonCamera.setPosition(Player->GetPosition() + glm::vec3(0, 1, 0));

//        cout << "position : " << Player->GetPosition()[1] << endl;
//        cout << "velocity : " << Player->getVelocity()[1] << endl;

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
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::L){
                glm::vec3 dir = firstPersonCamera.getEyeDirection();
                for(int i = 0; i < 3; i++) cout << dir[i] << " ";
                cout << "\n";
            }
        }

        clear();

        glClearStencil(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glEnable(GL_DEPTH);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glViewport(0, 0, 800, 600);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        //draw(sprite1);
        //draw(sprite2);

        gpu_obj_t::projection_matrix = camera->getPerspectiveMatrix();
        gpu_obj_t::view_matrix = camera->getModelViewMatrix();

        for(auto objs : gpuObjs) objs->draw();


        display();

        prevTime = nowTime;
    }

}

void GameWindow::MoveEvent() {

    float MoveSpeed = 7.0f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        glm::vec3 dir = firstPersonCamera.getEyeDirection();
        glm::vec2 dir2(dir[0], dir[2]);
        dir2 = glm::normalize(dir2);
        glm::vec3 newSpeed = glm::vec3(dir2[0], 0, dir2[1]) * MoveSpeed * 1.0f;
        newSpeed[1] = Player->getVelocity()[1];
        Player->setVelocity(newSpeed);
//        Player->Move(glm::vec3(dir2[0], 0, dir2[1]) * MoveSpeed * 0.01f);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        glm::vec3 dir = -firstPersonCamera.getEyeDirection();
        glm::vec2 dir2(dir[0], dir[2]);
        dir2 = glm::normalize(dir2);
        glm::vec3 newSpeed = glm::vec3(dir2[0], 0, dir2[1]) * MoveSpeed * 1.0f;
        newSpeed[1] = Player->getVelocity()[1];
        Player->setVelocity(newSpeed);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        glm::vec3 dir = -firstPersonCamera.getRightDirection();
        glm::vec2 dir2(dir[0], dir[2]);
        dir2 = glm::normalize(dir2);
        glm::vec3 newSpeed = glm::vec3(dir2[0], 0, dir2[1]) * MoveSpeed * 1.0f;
        newSpeed[1] = Player->getVelocity()[1];
        Player->setVelocity(newSpeed);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        glm::vec3 dir = firstPersonCamera.getRightDirection();
        glm::vec2 dir2(dir[0], dir[2]);
        dir2 = glm::normalize(dir2);
        glm::vec3 newSpeed = glm::vec3(dir2[0], 0, dir2[1]) * MoveSpeed * 1.0f;
        newSpeed[1] = Player->getVelocity()[1];
        Player->setVelocity(newSpeed);
    }
}
