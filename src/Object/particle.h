#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "gpu_object.h"
#include <vector>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>

class particle_t : public gpu_obj_t {
	void init() override;

public:
	void bind() override;
	void draw(glm::mat4 modelMatrix = glm::mat4(1)) override;
	particle_t();

};