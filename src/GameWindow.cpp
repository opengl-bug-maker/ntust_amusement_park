//
// Created by 林士傑 on 2022/12/6.
//

#include "GameWindow.h"

//#include "Object/gpu_object.h"

bool FUCKYOU = false;

GameWindow* GameWindow::magic;
glm::vec3 GameWindow::FallDownVector = glm::vec3(0, -20, 0);

//ostream& operator<<(ostream& os, const glm::vec3 & v)
//{
//    os << "(" << v.x << "," << v.y << "," << v.z << ")";
//    return os;
//}

GameWindow::GameWindow() {}

GameWindow::GameWindow(const sf::VideoMode &mode, const sf::String &title, sf::RenderWindow* result_win) : RenderWindow(mode, title, sf::Style::Default, sf::ContextSettings(
        24, // depthBits
        8,  // stencilBits
        4,  // antialiasingLevel
        3,  // majorVersion
        3,   // minorVersion
        sf::ContextSettings::Core
)) {
    result = result_win;
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
    window_size = make_pair(mode.width ,mode.height);
    prevTime = deltaClock.getElapsedTime();

    arcBall.setup(40, 100, -0.5, 0, 0);
    firstPersonCamera.setup(60, 8, 0, 0, 0);
    firstPersonCamera.lock();

//    camera = &firstPersonCamera;
    camera = &arcBall;
//endregion

    InitObjects();


    win_text.create(getSize().x, getSize().y);
}

void GameWindow::InitObjects() {
    cube::init_data();
    cylinder::init_data();
//region object
    gpu_obj_t* plane = new cube();
    plane->setName("plane");
    plane->SettingTransform(glm::vec3(0, -12, 0));
    plane->SettingScale(glm::vec3(50, 2, 50));
    plane->SetGravity(false);
    plane->SetTexture("../Images/skybox/top.jpg");



    gpuObjs.push_back(plane);
    Player = new player();
    Player->setName("player");
//    Player->SetGravity(false);
    Player->SettingTransform(glm::vec3(0, 0, 20));
    Player->SettingScale(glm::vec3(0.5, 2 ,0.5));
//    Player->SettingTransform(glm::vec3(0, 10, 0));
    gpuObjs.push_back(Player);

//
//    gpu_obj_t* piece = new Piece();
//    piece->setName("piece");
//    piece->SettingTransform(glm::vec3(3, 0, 3));
//    piece->SetGravity(false);
//    gpuObjs.push_back(piece);

//    gpu_obj_t* ball = new Ball();
//    ball->setName("ball");
//    ball->SettingScale(glm::vec3 (1, 0.1, 1));
//    ball->SetGravity(false);
//    gpuObjs.push_back(ball);

//    gpu_obj_t* smallCube = new cube();
//    smallCube->SetGravity(false);
//    smallCube->SettingTransform(glm::vec3(0, -3, 0));
//    smallCube->SetTexture("../Images/particle.png");
//    smallCube->setName("smallCube");
//
//    gpu_obj_t* bigCube = new cube();
//    bigCube->setName("bigCube");
//    bigCube->SettingTransform(glm::vec3(5, 0, 0));
//    bigCube->SetGravity(false);
//    bigCube->SetTexture("../Images/uvtemplate.jpg");
//    bigCube->addChildren(smallCube);
//    gpuObjs.push_back(bigCube);

//    gpu_obj_t* cc = new cube();
//    cc->setName("big cube");
////    cc->setFaceToCamera(true);
//    cc->SetGravity(false);
////    cc->SettingScale(glm::vec3(0.2,0.2,0.2));
//    cc->SettingScale(glm::vec3(1,1,1));
//    gpuObjs.push_back(cc);

    gpu_obj_t* c;

//    for(int i = 0; i < 10; i++){
//        c = new cube();
//        c->SettingTransform(glm::vec3 (5, -i, 5));
//        c->SettingScale(glm::vec3(0.2f, 0.2f, 0.2f));
//        c->SetGravity(false);
//        c->SetTexture("../Images/uvtemplate.jpg");
//        gpuObjs.push_back(c);
//    }

//     gpu_obj_t* c = new cube();
    /*c->setName("x cube");
    c->SettingTransform(glm::vec3(3, 0, 0));
    c->SettingScale(glm::vec3(0.5, 0.5, 0.5));
    c->SetGravity(false);
    gpuObjs.push_back(c);*/
    //cc->addChildren(c);

    c = new particle_t();
    c->setName("particle 0");
    c->SettingTransform(glm::vec3(45, -15.7, 45));
    c->SettingScale(glm::vec3(1, 1, 1));
    c->SetGravity(false);
    gpuObjs.push_back(c);

    c = new particle_t();
    c->setName("particle 1");
    c->SettingTransform(glm::vec3(-45, -15.7, -45));
    c->SettingScale(glm::vec3(1, 1, 1));
    c->SetGravity(false);
    gpuObjs.push_back(c);

    c = new particle_t();
    c->setName("particle 2");
    c->SettingTransform(glm::vec3(-45, -15.7, 45));
    c->SettingScale(glm::vec3(1, 1, 1));
    c->SetGravity(false);
    gpuObjs.push_back(c);

    c = new particle_t();
    c->setName("particle 3");
    c->SettingTransform(glm::vec3(45, -15.7, -45));
    c->SettingScale(glm::vec3(1, 1, 1));
    c->SetGravity(false);
    gpuObjs.push_back(c);


    rs = new RollerSystem();
    rs->setName("roller system");
    rs->SettingTransform(glm::vec3(0, -10, 0));
    rs->SetGravity(false);
    gpuObjs.push_back(rs);
////
    c = new ferris_wheel_t;
    c->setName("ferris_wheel 0");
    c->SettingTransform(glm::vec3(0, -10, 0));
    c->SettingScale(glm::vec3(1,1,1));
    c->SetGravity(false);
    gpuObjs.push_back(c);
//
    c = new locomotive_t;
    c->setName("locomotive 0");
    c->SettingTransform(glm::vec3(-2.5, -10, 5));
    c->SettingScale(glm::vec3(1,1,1));
    c->SetGravity(false);
    gpuObjs.push_back(c);
//
    c = new coach_t;
    c->setName("coach 0");
    c->SettingTransform(glm::vec3(2.5, -10, 5));
    c->SettingScale(glm::vec3(1,1,1));
    c->SetGravity(false);
    gpuObjs.push_back(c);
//
    c = new creeper_t;
    c->setName("creeper 0");
    c->SettingTransform(glm::vec3(-20,-10,20));
    c->SettingRotate(glm::vec3(0,90,0));
    c->SettingRotate(glm::vec3(3,3,3));
    c->SetGravity(false);
    gpuObjs.push_back(c);
//
    c = new creeper_t;
    c->setName("creeper 1");
    c->SettingTransform(glm::vec3(20,-10,20));
    c->SettingRotate(glm::vec3(0,90,0));
    c->SettingRotate(glm::vec3(3,3,3));
    c->SetGravity(false);
    gpuObjs.push_back(c);

//endregion
}
float kernel[3][3] = {
        {1, 1, 1},
        {1, 2, 1},
                {1, 1, 1}
};
//float kernel[5][5] = {
//        {1, 4, 6, 4, 1},
//        {4, 16, 24, 16, 4},
//        {6, 24, 36, 24, 6},
//        {4, 16, 24, 16, 4},
//        {1, 4, 6, 4, 1}
//};
//float kernel[7][7] = {
//        {0, 0, 0, 5, 0, 0, 0},
//        {0, 5, 18, 32, 18, 5, 0},
//        {0, 18, 64, 100, 64, 18, 0},
//        {5, 32, 100, 100, 100, 32, 5},
//        {0, 18, 64, 100, 64, 18, 0},
//        {0, 5, 18, 32, 18, 5, 0},
//        {0, 0, 0, 5, 0, 0, 0}
//
//};
//float kernel[5][5] = {
//        {1, 8, 12, 8, 1},
//        {8, 16, 36, 16, 4},
//        {6, 36, 72, 36, 6},
//        {4, 16, 36, 16, 4},
//        {1, 4, 6, 4, 1}
//};
const int height = 1200, width = 900;
void gray_and_inv(sf::Image& img){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            sf::Color c = img.getPixel(i, j);
            int v = 0.299 *(float)c.r + 0.587*(float)c.g + 0.114*(float)c.b;
            v = 255-v;
            img.setPixel(i, j, sf::Color(v, v, v));
        }
    }
}
void gray(sf::Image& img){
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            sf::Color c = img.getPixel(i, j);
            int v = 0.299 *(float)c.r + 0.587*(float)c.g + 0.114*(float)c.b;
            img.setPixel(i, j, sf::Color(v, v, v));
        }
    }
}
const int mxN = 256;
int nIntensityCount[mxN], nSumR[mxN], nSumG[mxN], nSumB[mxN];


void gauss(sf::Image& img){


    float d = 0;
//    for (int i = 0; i < 5; ++i) {
//        for (int j = 0; j < 5; ++j) {
//            kernel[i][j]*=2;
//        }
//    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            d += kernel[i][j];
        }
    }
    //cout<< d<<endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
                float sum_r = 0, sum_g = 0, sum_b = 0;
                for (int p = -1; p <= 1; ++p) {
                    for (int q = -1; q <= 1; ++q) {
                        int ni = i + p, nj = j + q;
                        if (ni < 0 || nj < 0 || ni >= height || nj >= width) { continue; }
                        //sum += t[k][ni][nj] * kernel[p + 2][q + 2];
                        sf::Color c = img.getPixel(ni, nj);
                        sum_r += c.r * kernel[p  +1][q +1];
                        sum_g += c.g * kernel[p +1][q+1 ];
                        sum_b += c.b*kernel[p+1][q+1];
                    }
                }
                img.setPixel(i, j, sf::Color(sum_r/d, sum_g/d, sum_b/d));
        }
    }
}
void pencil(sf::Image& img){

    sf::Image gray_img = img;
    sf::Image blurr_img = img;
    gray(gray_img);
    gray_and_inv(blurr_img);

    gauss(blurr_img);
    //def dodge(front,back): result=blurr*255/(255-gray)  result[result>255]=255 result[back==255]=255 return result.astype(‘uint8’)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float blurr_v = blurr_img.getPixel(i, j).r;
            float gray_v = gray_img.getPixel(i, j).r;
            if(255.0f-gray_v==0){gray_v+=2;}
            int v = blurr_v*255.0f/(255.0f-gray_v);
            v = std::min(255, v);
            img.setPixel(i, j, sf::Color(v, v, v));
        }
    }

}
void en(sf::Image& img){



    //def dodge(front,back): result=blurr*255/(255-gray)  result[result>255]=255 result[back==255]=255 return result.astype(‘uint8’)
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float R = img.getPixel(i, j).r;
            float G = img.getPixel(i, j).g;
            float B = img.getPixel(i, j).b;
            R = R*R*R/255;
            G = G*G*G/255;
            B = B*B*B/255;
            sf::Color c = sf::Color(R, G, B);
            img.setPixel(i, j, c);
        }
    }

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
                        gpuObjs[i]->PhysicsMove(collisionVec*0.999f);
                    }
//                    if(collisionVec[1] < -1){
//                        cout <<"wtf"<<endl;
//                    }
                    //if(gpuObjs[i]->getName() == "player" && gpuObjs[j]->getName() == "plane"){
                    if(gpuObjs[i]->getName() == "player"){
                        //cout << gpuObjs[i]->getName() << " phm " << gpuObjs[j]->getName() << collisionVec[1] << endl;
//                        ((PolygonCollider*)gpuObjs[i]->collider)->lookVertex();
//                        ((PolygonCollider*)gpuObjs[j]->collider)->lookVertex();
                    }
//                        cout << "posi : " << gpuObjs[i]->GetPosition() << endl;
                    glm::vec3 coll = glm::normalize(collisionVec);
                    if(glm::abs(glm::length(coll)) > 0.000000001){
                        float mul = glm::dot(gpuObjs[i]->getVelocity(), coll);
//                        if(mul < 0)
                            gpuObjs[i]->addVelocity(coll * (-mul));
                    }
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

        if(rs != nullptr){
            if(rs->isRunning()){
                firstPersonCamera.Bias(rs->GetTrainDir());
                Player->MoveTo(rs->GetTrainPos() - glm::vec3(0, 6, 0));
            }
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

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F){
                ::FUCKYOU = !::FUCKYOU;
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


        //display();
        glClearStencil(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glEnable(GL_DEPTH);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glViewport(0, 0, this->window_size.first, this->window_size.second);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if(camera == &arcBall) Player->setVisible(true);
        else Player->setVisible(false);
        


        gpu_obj_t::projection_matrix = camera->getPerspectiveMatrix();
        gpu_obj_t::view_matrix = camera->getModelViewMatrix();


        for(auto objs : gpuObjs) objs->draw();

//  fancy mirror (don't open, gpu killer)
//        for(auto& obj:gpuObjs){
//            if(obj->getName()=="plane"){
//                (*obj->sf_texture) = win_text;
//            }
//        }

        //cout<< this->getSize().x<<" "<<this->getSize().y<<endl;
        if(FUCKYOU){
            win_text.update((*this), 0, 0);
            sf::Image tmpImg = win_text.copyToImage();
            en(tmpImg);
            pencil(tmpImg);
            win_text.loadFromImage(tmpImg);
            this->result->draw(sf::Sprite(win_text));
            this->result->display();
            //this->result->setActive();
        }
        //this->result->draw(fb);
        //this->draw((sf::Sprite(win_text)));
        display();
//        win_text.update((*this), 0, 0);
//        sf::Image tmpImg = win_text.copyToImage();
//        tmpImg.saveToFile ("tmp.jpg");
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)){
        if(rs != nullptr)
            if(((player*)Player)->state != player::OnTrain)
                rs->Run();
        ((player*)Player)->state = player::OnTrain;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)){
        if(rs != nullptr)
            rs->GetOut();
        ((player*)Player)->state = player::Drop;
    }
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
