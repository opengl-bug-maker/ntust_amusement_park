//
// Created by ªL¤h³Ç on 2022/12/7.
//

#include "cylinder.h"
#include "cmath"
# define M_PI           3.14159265358979323846
cylinder::cylinder() {
    init();
}
double to_degree(double x) {
    return (x * 180.0) / M_PI;
}
vector<vector<double>> cal_cylinder_vertices() {
    //glBegin(GL_QUAD_STRIP);
    vector<vector<double>> ret_vertices;
    const int rate = 2;
    vector<double> upper_origin = { 0, 1, 0 };
    vector<double> lower_origin = { 0, -1, 0 };
    for (int j = 0; j <= 360; j += rate) {
        vector<double> lower_left = { cos(to_degree(j)), -1, sin(to_degree(j))};
        vector<double> lower_right = { cos(to_degree(j+1)), -1, sin(to_degree(j+1))};
        vector<double> upper_left = { cos(to_degree(j)), 1, sin(to_degree(j)) };
        vector<double> upper_right = { cos(to_degree(j + 1)), 1, sin(to_degree(j + 1)) }; 

        //lower left sidebar
        ret_vertices.push_back(lower_left);
        ret_vertices.push_back(lower_right);
        ret_vertices.push_back(upper_left);

        //upper right sidebar
        ret_vertices.push_back(upper_left);
        ret_vertices.push_back(upper_right);
        ret_vertices.push_back(upper_origin);

        //top
        ret_vertices.push_back(lower_left);
        ret_vertices.push_back(lower_right);
        ret_vertices.push_back(lower_origin);
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
    cout << ret_vertices.size() << endl;
    return ret_vertices;
}
void cylinder::init() {
    gpu_obj_t::init();

    this->model_matrix = glm::scale(this->model_matrix, glm::vec3(1.0f, 1.0f, 1.0f));
    vector<vector<double>> cylinder_vertices = cal_cylinder_vertices();
    this->vertexCount = cylinder_vertices.size()*3;
    const int vertexN = cylinder_vertices.size() * 3;
    this->data_block_size = { 3, 3};



    const int mxN = 1e5;
    this->data = new float[mxN];
    int i_data = 0;
    //cout << vertexN * 3 << endl;
    for (int i = 0; i < cylinder_vertices.size(); ++i) {
        data[i_data++] = cylinder_vertices[i][0]; //x 
        data[i_data++] = cylinder_vertices[i][1]; //y
        data[i_data++] = cylinder_vertices[i][2]; //z
    }
    //for (int i = 0; i < cylinder_vertices.size(); ++i) {
    //    data[i_data++] = 200; //x 
    //    data[i_data++] = 145; //y
    //    data[i_data++] = 89; //z
    //}
    this->vao->element_amount = cylinder_vertices.size();

    element = new GLuint[vertexN];
    for (int i = 0; i < vertexN; ++i) { element[i] = i; }

    collider = new BoxCollider();
}

void cylinder::bind() {
    if (this->shader) return;

    this->shader = new
        Shader(
            "box.vert",
            nullptr, nullptr, nullptr,
            "box.frag");
    this->shader->Use();
    gpu_obj_t::bind();
}
