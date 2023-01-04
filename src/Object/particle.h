#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "gpu_object.h"
#include <vector>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/norm.hpp>
struct Particle {
    glm::vec3 pos, speed = glm::vec3(0, 0, 0);
    glm::vec2 blast_dir;
    unsigned char r, g, b, a; // Color
    float size, angle, weight;
    float life; // Remaining life of the particle. if <0 : dead and unused.
    float cameradistance; // *Squared* distance to the camera. if dead : -1.0f
    bool blasted = false;
    bool operator<(const Particle& that) const {
        // Sort in reverse order : far particles drawn first.
        return this->cameradistance > that.cameradistance;
    }
};
const int MaxParticles = 50;
class particle_t : public gpu_obj_t {
	void init() override;
	float start_time = 0.0f;
public:
    Particle ParticlesContainer[MaxParticles];
    int LastUsedParticle = 0;
    int FindUnusedParticle();
    void SortParticles();
	void bind() override;
	void draw(glm::mat4 modelMatrix = glm::mat4(1)) override;
	particle_t();

};