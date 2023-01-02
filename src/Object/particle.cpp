#include "particle.h"
#include "GameWindow.h"
#include "iostream"

struct Particle {
	glm::vec3 pos, speed = glm::vec3(0, 0, 0);
	unsigned char r, g, b, a; // Color
	float size, angle, weight;
	float life; // Remaining life of the particle. if <0 : dead and unused.
	float cameradistance; // *Squared* distance to the camera. if dead : -1.0f

	bool operator<(const Particle& that) const {
		// Sort in reverse order : far particles drawn first.
		return this->cameradistance > that.cameradistance;
	}
};
const int MaxParticles = 20;
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
static const GLfloat g_vertex_buffer_data[] = { //adapt triangle strips into trangles to fit gpu_object
 -1.0f, -1.0f, 0.0f,
  1.0f, -1.0f, 0.0f,
 -1.0f,  1.0f, 0.0f,

  1.0f,  1.0f, 0.0f,
  1.0f, -1.0f, 0.0f,
 -1.0f,  1.0f, 0.0f,
};
//static const GLfloat g_vertex_buffer_data[] = { //adapt triangle strips into trangles to fit gpu_object
// -0.5f, -0.5f, 0.0f,
//  0.5f, -0.5f, 0.0f,
// -0.5f,  0.5f, 0.0f,
//
//  0.5f,  0.5f, 0.0f,
//  0.5f, -0.5f, 0.0f,
// -0.5f,  0.5f, 0.0f,
//};
//static const GLfloat g_vertex_buffer_data[] = { //adapt triangle strips into trangles to fit gpu_object
// -0.1f, -0.1f, 0.0f,
//  0.1f, -0.1f, 0.0f,
// -0.1f,  0.1f, 0.0f,
//
//  0.1f,  0.1f, 0.0f,
//  0.1f, -0.1f, 0.0f,
// -0.1f,  0.1f, 0.0f,
//};
void particle_t::init(){
	gpu_obj_t::init();
	this->model_matrix = glm::scale(this->model_matrix, glm::vec3(1.0f, 1.0f, 1.0f));
	start_time = (GLfloat)(GameWindow::magic->nowTime.asSeconds());
	this->vertexCount = MaxParticles*6;

	this->data_block_size = {3,3,2};
	for (int i = 0; i < MaxParticles; i++) {
		ParticlesContainer[i].life = -1.0f;
		ParticlesContainer[i].cameradistance = -1.0f;
	}


	this->data = new float[100000]; //adapt triangle strips into trangles to fit gpu_object(particleN* 2(traingles)*3(vertices)*3(x, y, z)

	
	this->vao->element_amount = MaxParticles * 2; //there are 2 triangles in each particles
	this->element = new GLuint[100000];
	for (int i = 0; i < 2 * MaxParticles*2*2; ++i) { element[i] = i; }
	//collider = new BoxCollider();
}

void particle_t::bind(){
	if (this->shader) return;
	this->shader = new
		Shader(
			"fireworks.vert",
			nullptr,
			nullptr,
			 "fireworks.geom",
			"fireworks.frag");
	this->shader->Use();
	//this->texture = new Texture2D();
	////this->texture->set2dTexture("particle.jpg");
	
	//this->texture->bind(0);
	//glUniform1i(glGetUniformLocation(this->shader->Program, "u_texture"), 0);
	this->sf_texture.loadFromFile("../Images/particle.png");
	
	glUniform1f(
		glGetUniformLocation(this->shader->Program, "start_time"), (GLfloat)(GameWindow::magic->nowTime.asSeconds()));
	gpu_obj_t::bind();
}

void particle_t::draw(glm::mat4 modelMatrix){
	if (!visible)
		return;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	this->shader->Use();
	sf::Texture::bind(&sf_texture);
	float nowTime = (int)((GLfloat)(GameWindow::magic->nowTime.asSeconds()));
//	float delta_time = 0.33;
	float delta_time = 0.033;
	//cout << delta_time << endl;
	int new_particlesN = min((float)1,delta_time*100);

	for (int i = 0; i < new_particlesN; i++) {
		int particleIndex = FindUnusedParticle();
		ParticlesContainer[particleIndex].life = 30.0f; // This particle will live 5 seconds.
		ParticlesContainer[particleIndex].pos = glm::vec3(0, 0, -20.0f);
		//ParticlesContainer[particleIndex].pos = glm::vec3(0, 0, -0.0f);

		float spread = 1.5f;
		glm::vec3 maindir = glm::vec3(0.0f, 10.0f, 0.0f);
		glm::vec3 randomdir = glm::vec3(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f
		);

		ParticlesContainer[particleIndex].speed = maindir + randomdir * spread;


		// Very bad way to generate a random color
		ParticlesContainer[particleIndex].r = rand() % 128+128;
		ParticlesContainer[particleIndex].g = rand() % 128+128;
		ParticlesContainer[particleIndex].b = rand() % 128+128;
		ParticlesContainer[particleIndex].a = (rand() % 256) / 3;
		ParticlesContainer[particleIndex].size = (rand() % 1000) / 2000.0f + 0.1f;
	}


	// Simulate all particles
	int ParticlesCount = 0;
	for (int i = 0; i < MaxParticles; i++) {

		Particle& p = ParticlesContainer[i]; // shortcut
		if (p.life > 0.0f) {
			// Decrease life
			p.life -= delta_time;
			if (p.life > 0.0f) {
				// Simulate simple physics : gravity only, no collisions
				//p.speed += glm::vec3(0.0f, -0.981f, 0.0f) * (float)delta_time;
				p.pos += p.speed * (float)delta_time*0.5f;
				//p.cameradistance = glm::length2(p.pos - CameraPosition);
				//p.cameradistance = glm::length2(p.pos);
				//ParticlesContainer[i].pos += glm::vec3(0.0f,10.0f, 0.0f) * (float)delta_time;
			}
			else {
				// Particles that just died will be put at the end of the buffer in SortParticles();
				//p.cameradistance = -1.0f;
			}
			ParticlesCount++;
		}
	}
	SortParticles();
	int i_data = 0;
	for (int i = 0; i < MaxParticles; ++i) {
		Particle& p = ParticlesContainer[i]; // shortcut
		for (int j = 0; j < 6; j++) {
			this->data[i_data++] = p.pos.x+ g_vertex_buffer_data[3*j];
			this->data[i_data++] = p.pos.y+ g_vertex_buffer_data[3*j+1];
			this->data[i_data++] = p.pos.z+ g_vertex_buffer_data[3*j+2];
		}
	}
	//for (int i = 0; i < i_data; ++i) { cout << (int)this->data[i] << " "; }cout << endl;
	//system("PAUSE");
	for (int i = 0; i < MaxParticles; ++i) {
		Particle& p = ParticlesContainer[i]; // shortcut
		for (int j = 0; j < 6; j++) {
			this->data[i_data++] = p.r/256.0;
			this->data[i_data++] = p.g / 256.0;
			this->data[i_data++] = p.b / 256.0;
		}
	}
	for (int i = 0; i < MaxParticles; ++i) {
		Particle& p = ParticlesContainer[i]; // shortcut

		this->data[i_data++] = 0.0f;
		this->data[i_data++] = 1.0f;

		this->data[i_data++] = 1.0f;
		this->data[i_data++] = 1.0f;

		this->data[i_data++] = 0.0f;
		this->data[i_data++] = 0.0f;

		this->data[i_data++] = 1.0f;
		this->data[i_data++] = 0.0f;

		this->data[i_data++] = 1.0f;
		this->data[i_data++] = 1.0f;

		this->data[i_data++] = 0.0f;
		this->data[i_data++] = 0.0f;


	}

	glUniform1f(
		glGetUniformLocation(this->shader->Program, "now_time"), (GLfloat)(GameWindow::magic->nowTime.asSeconds()));
	glUniformMatrix4fv(
		glGetUniformLocation(this->shader->Program, "u_projection"), 1, GL_FALSE, glm::value_ptr(gpu_obj_t::projection_matrix));

	//gpu_obj_t::bind();
	gpu_obj_t::update();
	gpu_obj_t::draw();
    sf::Texture::bind(nullptr);
}

particle_t::particle_t(){
	init();
}
