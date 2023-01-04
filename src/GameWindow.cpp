//
// Created by 林士傑 on 2022/12/6.
//

#include "GameWindow.h"
//#include "Object/ferris_wheel/ferwheel_namespace.h"

//#include "Object/gpu_object.h"

GameWindow* GameWindow::magic;
glm::vec3 GameWindow::FallDownVector = glm::vec3(0, -20, 0);

//ostream& operator<<(ostream& os, const glm::vec3 & v)
//{
//    os << " x : " << v.x << " y : " << v.y << " z : " << v.z;
//    return os;
//}

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

    arcBall.setup(40, 100, -0.5, 0, 0);
    firstPersonCamera.setup(60, 8, 0, 0, 0);
    firstPersonCamera.lock();

//    camera = &firstPersonCamera;
    camera = &arcBall;
//endregion

    InitObjects();
}

void GameWindow::InitObjects() {
//region object
    gpu_obj_t* plane = new cube();
    plane->setName("plane");
    plane->SettingTransform(glm::vec3(0, -11.7, 0));
    plane->SettingScale(glm::vec3(10, 2, 10));
    plane->SetGravity(false);
    plane->SetTexture("../Images/skybox/top.jpg");
    gpuObjs.push_back(plane);

    Player = new player();
    Player->setName("player");
//    Player->SetGravity(false);
    Player->SettingTransform(glm::vec3(0, 30, 8));
    Player->SettingScale(glm::vec3(1, 2, 1));
//    Player->SettingTransform(glm::vec3(0, 10, 0));
    gpuObjs.push_back(Player);


    gpu_obj_t* piece = new Piece();
    piece->setName("piece");
    piece->SettingTransform(glm::vec3(3, 0, 3));
    piece->SetGravity(false);
    gpuObjs.push_back(piece);

//    gpu_obj_t* ball = new Ball();
//    ball->setName("ball");
//    ball->SettingScale(glm::vec3 (1, 0.1, 1));
//    ball->SetGravity(false);
//    gpuObjs.push_back(ball);

    gpu_obj_t* smallCube = new cube();
    smallCube->SetGravity(false);
    smallCube->SettingTransform(glm::vec3(0, -3, 0));
    smallCube->SetTexture("../Images/particle.png");
    smallCube->setName("smallCube");

    gpu_obj_t* bigCube = new cube();
    bigCube->setName("bigCube");
    bigCube->SettingTransform(glm::vec3(5, 0, 0));
    bigCube->SetGravity(false);
    bigCube->SetTexture("../Images/uvtemplate.jpg");
    bigCube->addChildren(smallCube);
    gpuObjs.push_back(bigCube);

//    gpu_obj_t* cc = new cube();
//    cc->setName("big cube");
////    cc->setFaceToCamera(true);
//    cc->SetGravity(false);
////    cc->SettingScale(glm::vec3(0.2,0.2,0.2));
//    cc->SettingScale(glm::vec3(1,1,1));
//    gpuObjs.push_back(cc);

    gpu_obj_t* c;

    for(int i = 0; i < 10; i++){
        c = new cube();
        c->SettingTransform(glm::vec3 (5, -i, 5));
        c->SettingScale(glm::vec3(0.2f, 0.2f, 0.2f));
        c->SetGravity(false);
        c->SetTexture("../Images/uvtemplate.jpg");
        gpuObjs.push_back(c);
    }

//     gpu_obj_t* c = new cube();
    /*c->setName("x cube");
    c->SettingTransform(glm::vec3(3, 0, 0));
    c->SettingScale(glm::vec3(0.5, 0.5, 0.5));
    c->SetGravity(false);
    gpuObjs.push_back(c);*/
    //cc->addChildren(c);

    c = new particle_t();
    c->setName("particle 0");
    c->SettingTransform(glm::vec3(0, 0, 0));
    c->SettingScale(glm::vec3(1, 1, 1));
    c->SetGravity(false);
    gpuObjs.push_back(c);


    rs = new RollerSystem();
    rs->setName("roller system");
    rs->SetGravity(false);
    gpuObjs.push_back(rs);

    c = new ferris_wheel_t;
    c->setName("ferris_wheel 0");
    c->SettingTransform(glm::vec3(0, 0, 0));
    c->SettingScale(glm::vec3(1,1,1));
    c->SetGravity(false);
    gpuObjs.push_back(c);

    c = new locomotive_t;
    c->setName("locomotive 0");
    c->SettingTransform(glm::vec3(0, -10, 0));
    c->SettingScale(glm::vec3(1,1,1));
    c->SetGravity(false);
    gpuObjs.push_back(c);

    c = new coach_t;
    c->setName("coach 0");
    c->SettingTransform(glm::vec3(5, -10, 0));
    c->SettingScale(glm::vec3(1,1,1));
    c->SetGravity(false);
    gpuObjs.push_back(c);

//endregion
}

void GameWindow::run() {
    for(auto objs : gpuObjs) objs->bind();

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
                    if(glm::length(collisionVec) > 0.1){
//                        cout << gpuObjs[i]->getName() << " phm " << collisionVec << endl;
//                        cout << "posi : " << gpuObjs[i]->GetPosition() << endl;
                        gpuObjs[i]->PhysicsMove(collisionVec);
                    }
//                        cout << gpuObjs[i]->getName() << " phm " << collisionVec << endl;
//                        cout << "posi : " << gpuObjs[i]->GetPosition() << endl;
                    glm::vec3 coll = glm::normalize(collisionVec);
                    if(glm::abs(glm::length(coll)) > 0.000000001)
                        gpuObjs[i]->addVelocity(coll * (-glm::dot(gpuObjs[i]->getVelocity(), coll)));
                }
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && ((player*)Player)->state == player::ActionState::Floor){
//            cout << "jump" << endl;
            ((player*)Player)->state = player::ActionState::Drop;
            glm::vec3 jump = glm::vec3 (0, 10, 0);
            jump[0] = Player->getVelocity()[0];
            jump[2] = Player->getVelocity()[2];
            Player->setVelocity(jump);
        }


        for(auto objs : gpuObjs) objs->UpdatePosition(deltaTime);

        if(rs->isRunning()){
            firstPersonCamera.Bias(rs->GetTrainDir());
            Player->MoveTo(rs->GetTrainPos() - glm::vec3(0, 6, 0));
        }

        firstPersonCamera.setPosition(Player->GetPosition() + glm::vec3(0, 1, 0));

//        cout << "position : " << Player->GetPosition()[1] << endl;
//        cout << "velocity : " << Player->getVelocity()[1] << endl;

        sf::Event event;
        while (pollEvent(event)) {

            camera->handle(event);

            if (event.type == sf::Event::Closed){
                close();return;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                close();return;
            }

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

        if(camera == &arcBall) Player->setVisible(true);
        else Player->setVisible(false);
        
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
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)){
//        if(rs != nullptr)
//            if(((player*)Player)->state != player::OnTrain)
//                rs->Run();
//        ((player*)Player)->state = player::OnTrain;
//    }
//    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
//        if(rs != nullptr)
//            rs->GetOut();
//        ((player*)Player)->state = player::Drop;
//    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)){
        for(auto obj : gpuObjs){
            if(obj->getName() == "big cube"){
                obj->setFaceToCamera(!obj->isFaceToCamera());
            }
        }
    }
}

void GameWindow::ConsoleEvent(string input) {
    if(input == "reset"){
        Player->MoveTo(glm::vec3(0, 0, 0));
        Player->setVelocity(glm::vec3(0, 0, 0));
        Player->SetGravity(false);
        cout << "move!" << endl;
    }
    if(input == "unfreeze"){
        Player->SetGravity(true);
    }
    if(input == "posi"){
        cout << Player->GetPosition()[0] << " "<< Player->GetPosition()[1] << " "<< Player->GetPosition()[2] << endl;
    }
    if(input == "q"){
        firstPersonCamera.Bias(glm::vec3(-1,0,-1));
    }
}
