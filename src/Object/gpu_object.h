#pragma once

//#ifdef GPU_OBJECT

#include "RenderUtilities/Shader.h"
#include "RenderUtilities/Texture.h"
#include "RenderUtilities/BufferObject.h"
#include "Utilities/3DUtils.h"
#include "glm/mat4x4.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Object/PhysicsObject.h"

class empty_obj;
class cube;

class gpu_obj_t : public PhysicsObject {
protected:
    bool visible = true;

	Texture2D* texture = nullptr; //init

	VAO* vao = new VAO; //multiple vbos and 1 ebo
    GLuint* element = nullptr; //init

    size_t vertexCount;
	GLfloat* data = nullptr; //init
    vector<size_t> data_block_size; //init

    vector<gpu_obj_t*> children; //init

	virtual void init();

	void update(float* input_data, size_t index);

public:
    static glm::mat4 projection_matrix;
    static glm::mat4 view_matrix;

	virtual void bind();
	Shader* shader = nullptr; //init
	gpu_obj_t();

	explicit gpu_obj_t(glm::mat4 model_matrix);

    void addChildren(gpu_obj_t* obj);

    void draw(glm::mat4 modelMatrix = glm::mat4(1));
};