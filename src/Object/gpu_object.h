#pragma once

//#ifdef GPU_OBJECT

#include "RenderUtilities/Shader.h"
#include "RenderUtilities/Texture.h"
#include "RenderUtilities/BufferObject.h"
#include "Utilities/3DUtils.h"
#include "glm/mat4x4.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class gpu_obj_t {
protected:
	Texture2D* texture = nullptr; //init

    glm::mat4 model_matrix = glm::mat4(1); //for scale, rotation, translation

	VAO* vao = new VAO; //multiple vbos and 1 ebo
    GLuint* element = nullptr; //init

    size_t vertexCount;
	GLfloat* data = nullptr; //init
    vector<size_t> data_block_size; //init

    vector<gpu_obj_t*> children; //init

	virtual void init();

	void update(float* input_data, size_t index);

    //Gaming

    bool GravityObject = true;

    glm::vec3 velocity = glm::vec3(0);

public:
    static glm::mat4 projection_matrix;
    static glm::mat4 view_matrix;

	virtual void bind();
	Shader* shader = nullptr; //init
	gpu_obj_t();
	explicit gpu_obj_t(GLfloat* input_data);
	explicit gpu_obj_t(glm::mat4 model_matrix);
	explicit gpu_obj_t(GLfloat* input_data, glm::mat4 model_matrix);

    void SetPosition(glm::vec3 position);
    void Translate(glm::vec3 translate);
    void Scale(glm::vec3 scale);
    void addChildren(gpu_obj_t* obj);

    void draw(glm::mat4 modelMatrix = glm::mat4(1));

    //Gaming

    void SetGravity(bool isGravity);

    const glm::vec3 &getVelocity() const;

    void setVelocity(const glm::vec3 &velocity);

    void UpdatePosition(sf::Time deltaTime);

    void FallDown(sf::Time deltaTime);
};