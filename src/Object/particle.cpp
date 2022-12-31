#include "particle.h"
#include "GameWindow.h"
struct Particle {
	glm::vec3 pos, speed;
	unsigned char r, g, b, a; // Color
	float size, angle, weight;
	float life; // Remaining life of the particle. if <0 : dead and unused.
	float cameradistance; // *Squared* distance to the camera. if dead : -1.0f

	bool operator<(const Particle& that) const {
		// Sort in reverse order : far particles drawn first.
		return this->cameradistance > that.cameradistance;
	}
};
const int MaxParticles = 1000;
Particle ParticlesContainer[MaxParticles];
int LastUsedParticle = 0;

int FindUnusedParticle() {

	for (int i = LastUsedParticle; i < MaxParticles; i++) {
		if (ParticlesContainer[i].life < 0) {
			LastUsedParticle = i;
			return i;
		}
	}

	for (int i = 0; i < LastUsedParticle; i++) {
		if (ParticlesContainer[i].life < 0) {
			LastUsedParticle = i;
			return i;
		}
	}

	return 0; // All particles are taken, override the first one
}
void SortParticles() {
	std::sort(&ParticlesContainer[0], &ParticlesContainer[MaxParticles]);
}

void particle_t::init(){
	gpu_obj_t::init();
	this->model_matrix = glm::scale(this->model_matrix, glm::vec3(1.0f, 1.0f, 1.0f));

	this->vertexCount = 18;

	this->data_block_size = {3};

	static GLfloat* g_particule_position_size_data = new GLfloat[MaxParticles * 4];
	static GLubyte* g_particule_color_data = new GLubyte[MaxParticles * 4];
	for (int i = 0; i < MaxParticles; i++) {
		ParticlesContainer[i].life = -1.0f;
		ParticlesContainer[i].cameradistance = -1.0f;
	}

	//static const GLfloat g_vertex_buffer_data[] = { //adapt triangle strips into trangles to fit gpu_object
	// -0.5f, -0.5f, 0.0f,
	//  0.5f, -0.5f, 0.0f,
	// -0.5f,  0.5f, 0.0f,

	//  0.5f,  0.5f, 0.0f,
	//  0.5f, -0.5f, 0.0f,
	// -0.5f,  0.5f, 0.0f,
	//};
	this->data = new float[]{ //adapt triangle strips into trangles to fit gpu_object
		 -0.5f, -0.5f, 0.0f,
		  0.5f, -0.5f, 0.0f,
		 -0.5f,  0.5f, 0.0f,

		  0.5f,  0.5f, 0.0f,
		  0.5f, -0.5f, 0.0f,
		 -0.5f,  0.5f, 0.0f,
	};
	this->vao->element_amount = MaxParticles * 2; //there are 2 triangles in each particles
	this->element = new GLuint[6*MaxParticles];
	for (int i = 0; i < 6 * MaxParticles; ++i) { element[i] = i; }
	//collider = new BoxCollider();
}

void particle_t::bind(){
	if (this->shader) return;
	this->shader = new
		Shader(
			"box.vert",
			nullptr, nullptr, nullptr,
			"box.frag");
	this->shader->Use();
	//this->texture = new Texture2D();
	////this->texture->set2dTexture("particle.jpg");

	//this->texture->bind(0);
	//glUniform1i(glGetUniformLocation(this->shader->Program, "u_texture"), 0);

	glUniform1f(
		glGetUniformLocation(this->shader->Program, "start_time"), (GLfloat)(GameWindow::magic->nowTime.asSeconds()));
	gpu_obj_t::bind();
}

void particle_t::draw(glm::mat4 modelMatrix){
	if (!visible)
		return;
	this->shader->Use();
	glUniform1f(
		glGetUniformLocation(this->shader->Program, "now_time"), (GLfloat)(GameWindow::magic->nowTime.asSeconds()));
	glUniformMatrix4fv(
		glGetUniformLocation(this->shader->Program, "u_projection"), 1, GL_FALSE, glm::value_ptr(gpu_obj_t::projection_matrix));
	gpu_obj_t::draw();
}

particle_t::particle_t(){
	init();
}
