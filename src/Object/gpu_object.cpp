#include "gpu_object.h"
#include "GameWindow.h"
#include "Object/PhysicsObject.h"
glm::mat4 gpu_obj_t::projection_matrix;
glm::mat4 gpu_obj_t::view_matrix;

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