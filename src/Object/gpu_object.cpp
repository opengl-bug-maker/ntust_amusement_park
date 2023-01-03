#include "gpu_object.h"
#include "GameWindow.h"
#include "Object/PhysicsObject.h"
glm::mat4 gpu_obj_t::projection_matrix;
glm::mat4 gpu_obj_t::view_matrix;

ostream& operator<<(ostream& os, const glm::vec3 & v)
{
    os << " x : " << v.x << " y : " << v.y << " z : " << v.z;
    return os;
}

gpu_obj_t::gpu_obj_t() {

}

gpu_obj_t::gpu_obj_t(glm::mat4 model_matrix) {
    this->model_matrix = model_matrix;
}

void gpu_obj_t::init() {
	
}

void gpu_obj_t::bind() {
    glGenVertexArrays(1, &this->vao->vao);
    glGenBuffers(data_block_size.size(), this->vao->vbo);
    glGenBuffers(1, &this->vao->ebo);

    glBindVertexArray(this->vao->vao);

    size_t startIndex = 0;
    size_t total = 0;
    for(auto s : data_block_size) total += s;

    for(int i = 0; i < data_block_size.size(); i++){
        glBindBuffer(GL_ARRAY_BUFFER, vao->vbo[i]);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * total * sizeof(GLfloat), data, GL_STREAM_DRAW);
        glVertexAttribPointer(i, data_block_size[i], GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat), (void*)(startIndex * sizeof(GLfloat)));
        glEnableVertexAttribArray(i);
        startIndex += vertexCount * data_block_size[i];
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vao->element_amount * 3 * sizeof(GLuint), element, GL_STREAM_DRAW);

    glBindVertexArray(0);

    for(auto objs : children) objs->bind();
}

void gpu_obj_t::update(float* input_data, size_t index) {
	//input_data -> whole data -> choose perticular segment to update
	//int start = 0;
	//for(int i = 0; i < index - 1; i++)
	//	start += data_block_size[i];
	//start *= this->vao->element_amount;
	//for(int i = 0; i < data_block_size[index] * this->vao->element_amount; i++){
	//	this->data[start + i] = input_data[i];
	//}
        
}
void gpu_obj_t::update() {
    size_t startIndex = 0;
    size_t total = 0;
    for (auto s : data_block_size) total += s;
    for (int i = 0; i < data_block_size.size(); i++) {
        glBindBuffer(GL_ARRAY_BUFFER, vao->vbo[i]);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount * total * sizeof(GLfloat), data);
        //glBufferData(GL_ARRAY_BUFFER, vertexCount * total * sizeof(GLfloat), data, GL_STREAM_DRAW);
        glVertexAttribPointer(i, data_block_size[i], GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat), (void*)(startIndex * sizeof(GLfloat)));
        glEnableVertexAttribArray(i);
        startIndex += vertexCount * data_block_size[i];
    }
}
void gpu_obj_t::addChildren(gpu_obj_t* obj) {
    children.push_back(obj);
}

void gpu_obj_t::draw(glm::mat4 modelMatrix) {
    if(!visible)
        return;
    if (getName() == "wheel") { 
        int i = 0; 
    }
	modelMatrix = modelMatrix * this->model_matrix;
    if(faceToCamera){
        glm::vec3 dir = GetPosition() - GameWindow::magic->firstPersonCamera.getEyePosition();
        dir = glm::normalize(dir);
        glm::vec2 hor = glm::vec2(dir[2], dir[0]);

        double st = dir[1];
        double ct = glm::length(hor);

        hor = glm::normalize(hor);
        double sp = -hor[1];
        double cp = hor[0];

        glm::mat4 ModelView = glm::mat4(
                cp,  st * sp, -ct * sp, 0,
                0,       ct,       st, 0,
                sp, -st * cp, ct * cp, 0,
                0,        0,       0,1
        );
        modelMatrix = modelMatrix * glm::inverse(ModelView);
    }
	for(auto& child : children){
		child->draw(modelMatrix);
	}
    if(this->shader)
	    this->shader->Use();
    else { return; }

    glUniformMatrix4fv(
            glGetUniformLocation(this->shader->Program, "u_projection"), 1, GL_FALSE, glm::value_ptr(gpu_obj_t::projection_matrix));

    glUniformMatrix4fv(
            glGetUniformLocation(this->shader->Program, "u_view"), 1, GL_FALSE, glm::value_ptr(gpu_obj_t::view_matrix));

	glUniformMatrix4fv( //warning : model matrix name
		glGetUniformLocation(this->shader->Program, "u_model"), 1, GL_FALSE, &modelMatrix[0][0]);

	glBindVertexArray(vao->vao);
	glDrawElements(GL_TRIANGLES, vao->element_amount * 3, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glUseProgram(0);
}

bool gpu_obj_t::isVisible() const {
    return visible;
}

void gpu_obj_t::setVisible(bool visible) {
    gpu_obj_t::visible = visible;
}

bool gpu_obj_t::isFaceToCamera() const {
    return faceToCamera;
}

void gpu_obj_t::setFaceToCamera(bool faceToCamera) {
    gpu_obj_t::faceToCamera = faceToCamera;
}

bool gpu_obj_t::IsCollision(PhysicsObject *obj, glm::vec3 &collisionVector) {
    for(auto child : children){
        for(auto objChild : ((gpu_obj_t*)obj)->children)
            if(child->IsCollision(objChild, collisionVector))
                return true;
    }
    for(auto objChild : ((gpu_obj_t*)obj)->children)
        if(this->IsCollision(objChild, collisionVector))
            return true;
//    if(obj->getName() == "player")
//        cout << getName() << " " << to_string(children.size()) << " " << obj->getName() << endl;
//    if(obj->getName() == "rollCar")
//        cout << getName() << " " << to_string(children.size()) << " " << obj->getName() << endl;
//    if(getName() == "rollCar" && obj->getName() == "player")
//        cout << getName() << " " << to_string(children.size()) << " " << obj->getName() << endl;
    bool bbb = PhysicsObject::IsCollision(obj, collisionVector);
    if(getName() == "player" && obj->getName() == "rollCar"){
//        cout << getName() << " " << to_string(children.size()) << " " << obj->getName() << "   " << to_string(bbb) << endl;
//        cout << ((BoxCollider*)this->collider)->center << " | " << ((BoxCollider*)this->collider)->size << " || ";
//        cout << ((BoxCollider*)((gpu_obj_t*)obj)->collider)->center << " | " << ((BoxCollider*)((gpu_obj_t*)obj)->collider)->size << endl;

    }
    return bbb;
}
