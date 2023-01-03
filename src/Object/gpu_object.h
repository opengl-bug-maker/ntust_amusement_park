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
class gpu_obj_t : public PhysicsObject  {
protected:
    bool visible = true;
    bool faceToCamera = false;

    Texture2D* texture = nullptr; //init
    sf::Texture* sf_texture = nullptr;
    VAO* vao = new VAO; //multiple vbos and 1 ebo

    GLuint* element = nullptr; //init
    size_t vertexCount;
    GLfloat* data = nullptr; //init

    vector<size_t> data_block_size; //init

    vector<gpu_obj_t*> children; //init

	virtual void init();
    void update(float* input_data, size_t index);

	void update();
public:
    static glm::mat4 projection_matrix;
    static glm::mat4 view_matrix;

	virtual void bind();
	Shader* shader = nullptr; //init
	gpu_obj_t();

    void SetTexture(string str);

	explicit gpu_obj_t(glm::mat4 model_matrix);

    void addChildren(gpu_obj_t* obj);
	
    virtual void draw(glm::mat4 modelMatrix = glm::mat4(1));

    bool isVisible() const;

    void setVisible(bool visible);

    bool isFaceToCamera() const;

    void setFaceToCamera(bool faceToCamera);

    bool IsCollision(PhysicsObject *obj, glm::vec3 &collisionVector) override;
};
