//
// Created by �L�h�� on 2022/12/7.
//

#include "cylinder.h"
#include "GameWindow.h"
#include "cmath"
# define M_PI           3.14159265358979323846
cylinder::cylinder() {
    init();
}
float to_radius(float x) {
    return (x / 180.0f) * M_PI;
}
pair<vector<vector<float>>, vector<vector<float>>> cal_cylinder_prop() {
    //glBegin(GL_QUAD_STRIP);
    vector<vector<float>> ret_vertices, ret_text;
    const int rate = 30; //error occurs in rate is too big
    vector<float> upper_origin = { 0.0f, 1.0f, 0.0f };
    vector<float> lower_origin = { 0.0f, -1.0f, 0.0f };
    for (int j = 0; j+rate <= 360; j += rate) {
        vector<float> lower_left = { cos(to_radius(j)), -1, sin(to_radius(j))};
        vector<float> lower_right = { cos(to_radius(j+rate)), -1, sin(to_radius(j+rate))};
        vector<float> upper_left = { cos(to_radius(j)), 1, sin(to_radius(j)) };
        vector<float> upper_right = { cos(to_radius(j + rate)), 1, sin(to_radius(j + rate)) };
//        cout<< "lf : ";for(auto& e:lower_left){cout<<e<<" ";}cout<<endl;
//        cout<< "lr : ";for(auto& e:lower_right){cout<<e<<" ";}cout<<endl;
//        cout<< "ul : ";for(auto& e:upper_left){cout<<e<<" ";}cout<<endl;
//        cout<< "ur : ";for(auto& e:upper_right){cout<<e<<" ";}cout<<endl;
        //lower right sidebar
        ret_vertices.push_back(lower_left);
        ret_vertices.push_back(lower_right);
        ret_vertices.push_back(upper_left);

        ret_text.push_back({0.34f, 1.0f});
        ret_text.push_back({0.0f, 1.0f});
        ret_text.push_back({0.34f, 0.0f});

//        ret_text.push_back({0.0f, 1.0f});
//        ret_text.push_back({1.0f, 1.0f});
//        ret_text.push_back({1.0f, 0.0f});

        //upper left sidebar
        ret_vertices.push_back(upper_left);
        ret_vertices.push_back(upper_right);
        ret_vertices.push_back(lower_right);

//        ret_text.push_back({0.0f, 0.0f});
//        ret_text.push_back({1.0f, 0.0f});
//        ret_text.push_back({1.0f, 1.0f});
        ret_text.push_back({0.34f, 0.0f});
        ret_text.push_back({0.0f, 0.0f});
        ret_text.push_back({0.0f, 1.0f});

        //bottom
        ret_vertices.push_back(lower_left);
        ret_vertices.push_back(lower_right);
        ret_vertices.push_back(lower_origin);

        ret_text.push_back({0.0f, 0.0f});
        ret_text.push_back({0.0f, 1.0f});
        ret_text.push_back({1.0f, 0.5f});
//
//        //top
        ret_vertices.push_back(upper_left);
        ret_vertices.push_back(upper_right);
        ret_vertices.push_back(upper_origin);

        ret_text.push_back({0.0f, 0.0f});
        ret_text.push_back({0.0f, 1.0f});
        ret_text.push_back({1.0f, 0.5f});
    }

   // glBegin(GL_POLYGON);
   // for (int j = 0; j <= 360; j += rate) {
   //     glNormal3f(0, 1, 0);
   //     glVertex3f(cos(to_degree(j)), 1, sin(to_degree(j)));
   // }
   //// glEnd();


   // //glBegin(GL_POLYGON);
   // for (int j = 0; j <= 360; j += rate) {
   //     glNormal3f(0, -1, 0);
   //     glVertex3f(cos(to_degree(j)), -1, sin(to_degree(j)));
   // }
   // glEnd();
    //cout << ret_vertices.size() << endl;
    pair<vector<vector<float>>, vector<vector<float>>> ret;
    ret.first = ret_vertices; ret.second = ret_text;
    return ret;
}
void cylinder::init() {
    gpu_obj_t::init();

    this->model_matrix = glm::scale(this->model_matrix, glm::vec3(1.0f, 1.0f, 1.0f));
    auto cylinder_prop = cal_cylinder_prop();
    vector<vector<float>> cylinder_vertices = cylinder_prop.first;
    vector<vector<float>> cylinder_text = cylinder_prop.second;
    this->vertexCount = cylinder_vertices.size();
    cout<< vertexCount<<endl;
    const int elementN = cylinder_vertices.size();
    this->data_block_size = { 3, 3, 2};



    const int mxN = 1e5;
    this->data = new float[cylinder_vertices.size()*8];
    int i_data = 0;
    //cout << vertexN * 3 << endl;
    for (int i = 0; i < cylinder_vertices.size(); ++i) {
        data[i_data++] = cylinder_vertices[i][0]; //x 
        data[i_data++] = cylinder_vertices[i][1]; //y
        data[i_data++] = cylinder_vertices[i][2]; //z
    }
    for (int i = 0; i < cylinder_vertices.size(); ++i) {
        data[i_data++] = 0; //x
        data[i_data++] = 0; //y
        data[i_data++] = 0; //z
    }
    for (int i = 0; i < cylinder_text.size(); ++i) {
        data[i_data++] = cylinder_text[i][0]; //u
        data[i_data++] = cylinder_text[i][1]; //v
    }
//    cout<< i_data<<endl;
    this->vao->element_amount = cylinder_vertices.size();

    this->element = new GLuint[10001];
    for (int i = 0; i < elementN; ++i) { element[i] = i; }

    collider = new BoxCollider();
}

void cylinder::bind() {
    if (this->shader) return;

    //this->shader = new
    //        Shader(
    //        "explosion.vert",
    //        nullptr, nullptr, "explosion.geom",
    //        "explosion.frag");
    this->shader = new
    Shader(
        "pure_texture.vert",
        nullptr, nullptr, nullptr,
        "pure_texture.frag");
    this->shader->Use();
//    this->texture = new Texture2D();
//    //this->texture->set2dTexture("../Images/skybox/back.jpg");
//    this->texture->bind(0);
//    //uniform stuff
//    glUniform1i(glGetUniformLocation(this->shader->Program, "u_texture"), 0);

    glUniform1f(
        glGetUniformLocation(this->shader->Program, "start_time"), (GLfloat)(GameWindow::magic->nowTime.asSeconds()));
    

    //general input
    gpu_obj_t::bind();
}
void cylinder::draw(glm::mat4 modelMatrix) {
    if (!visible)
        return;
    this->shader->Use();
    glUniform1f(
        glGetUniformLocation(this->shader->Program, "now_time"), (GLfloat)(GameWindow::magic->nowTime.asSeconds()));
    glUniformMatrix4fv(
        glGetUniformLocation(this->shader->Program, "u_projection"), 1, GL_FALSE, glm::value_ptr(gpu_obj_t::projection_matrix));
    gpu_obj_t::draw(modelMatrix);
    //gpu_obj_t::draw();
}