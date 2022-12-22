#include "gpu_object.h"
#include "GameWindow.h"

glm::mat4 gpu_obj_t::projection_matrix;
glm::mat4 gpu_obj_t::view_matrix;

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
        glBufferData(GL_ARRAY_BUFFER, vertexCount * 3 * total * sizeof(GLfloat), data, GL_STATIC_DRAW);
        glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0 * sizeof(GLfloat), (void*)(startIndex * sizeof(GLfloat)));
        glEnableVertexAttribArray(i);
        startIndex += vertexCount * data_block_size[i];
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vao->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vao->element_amount * 3 * sizeof(GLuint), element, GL_STATIC_DRAW);

    glBindVertexArray(0);

    for(auto objs : children) objs->bind();
}

void gpu_obj_t::update(float* input_data, size_t index) {
	//input_data -> whole data -> choose perticular segment to update
	int start = 0;
	for(int i = 0; i < index - 1; i++)
		start += data_block_size[i];
	start *= this->vao->element_amount;
	for(int i = 0; i < data_block_size[index] * this->vao->element_amount; i++){
		this->data[start + i] = input_data[i];
	}
}

gpu_obj_t::gpu_obj_t() {

}

gpu_obj_t::gpu_obj_t(GLfloat* input_data) : data(input_data) {

}

gpu_obj_t::gpu_obj_t(glm::mat4 model_matrix) : model_matrix(model_matrix) {
}

gpu_obj_t::gpu_obj_t(GLfloat* input_data, glm::mat4 model_matrix) : data(input_data), model_matrix(model_matrix) {
}

void gpu_obj_t::draw(glm::mat4 modelMatrix) {
	//todo multi parent modelMatrix
	// modelMatrix * this->model_matrix
	modelMatrix = modelMatrix * this->model_matrix;
	for(auto child : children){
		child->draw(model_matrix);
	}
	//todo true draw
	this->shader->Use();

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

void gpu_obj_t::SetPosition(glm::vec3 position) {
    this->model_matrix = glm::mat4(1);
    this->model_matrix = glm::translate(this->model_matrix, position);
}

void gpu_obj_t::Translate(glm::vec3 translate) {
    this->model_matrix = glm::translate(this->model_matrix, translate);
    this->collider->Translate(translate);
}

void gpu_obj_t::Scale(glm::vec3 scale) {
    this->model_matrix = glm::scale(this->model_matrix, scale);
    this->collider->Scale(scale);
}

void gpu_obj_t::addChildren(gpu_obj_t* obj) {
    children.push_back(obj);
}

void gpu_obj_t::SetGravity(bool isGravity) {
    GravityObject = isGravity;
}

const glm::vec3 &gpu_obj_t::getVelocity() const {
    return velocity;
}

void gpu_obj_t::setVelocity(const glm::vec3 &velocity) {
    gpu_obj_t::velocity = velocity;
}

void gpu_obj_t::UpdatePosition(sf::Time deltaTime) {
    if(GravityObject){
        Translate(velocity * deltaTime.asSeconds());
    } else {
        velocity[0] = velocity[1] = velocity[2] = 0;
    }
}

void gpu_obj_t::FallDown(sf::Time deltaTime) {
    if(GravityObject)
        velocity += GameWindow::FallDownVector * deltaTime.asSeconds();
}

bool gpu_obj_t::IsCollision(gpu_obj_t* obj) {
    if(this == obj){
        std::cerr << "dont collision you self :X, loc at : " << this << std::endl;
        return false;
    }
    if(this->collider == nullptr || obj->collider == nullptr){
        return false;
    }
    return this->collider->IsCollision(obj->collider);
}
