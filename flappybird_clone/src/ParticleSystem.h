#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>
#include <SDL.h>
#include "Mesh.h"
#include "Shader.h"

struct Particle {
	int life_time;
	float rotation_speed;
	float velocity;
	float angle;
	glm::vec3 direction;
	glm::vec3 pos;
	int last_time;
	Mesh mesh;
};

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();
	void Init(glm::vec3 spawn_pos, glm::mat4 model);
	void Emmit(unsigned int cur_time, glm::vec3 spawn_pos, glm::mat4 model);
	void Update(glm::vec3 spawn_pos, glm::mat4 model);
	void Draw();
private:
	std::vector<Particle> particles;
	std::vector<float> particle_vert;
	int last_particle_time;
	glm::vec3 start_dir;
	float start_rotation_speed;
	glm::vec3 smoke_color;
	int start_life_time;
	float smoke_velocity;
	int smoke_del_time;
	Shader particle_shader;
};

