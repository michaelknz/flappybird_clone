#include "ParticleSystem.h"


ParticleSystem::ParticleSystem() {

}

ParticleSystem::~ParticleSystem() {

}

void ParticleSystem::Init(glm::vec3 spawn_pos, glm::mat4 model) {
	start_dir = glm::vec3(-1.0f, 0.0f, 0.0f);
	start_rotation_speed = 100.0f;
	smoke_color = glm::vec3(0.5f, 0.5f, 0.5f);
	start_life_time = 5.0f;
	smoke_velocity = 0.5f;
	smoke_del_time = 100;
	start_life_time = 2500;
	particle_shader.Init("particle_shader", "NULL");

	particle_vert = {
		-0.02f,-0.02f,0.0f,smoke_color.x,smoke_color.y,smoke_color.z,
		-0.02f,0.02f,0.0f,smoke_color.x,smoke_color.y,smoke_color.z,
		0.02f,-0.02f,0.0f,smoke_color.x,smoke_color.y,smoke_color.z,
		-0.02f,0.02f,0.0f,smoke_color.x,smoke_color.y,smoke_color.z,
		0.02f,0.02f,0.0f,smoke_color.x,smoke_color.y,smoke_color.z,
		0.02f,-0.02f,0.0f,smoke_color.x,smoke_color.y,smoke_color.z,
	};

	Emmit(SDL_GetTicks(), spawn_pos, model);
}

void ParticleSystem::Emmit(unsigned int cur_time, glm::vec3 spawn_pos, glm::mat4 model) {
	Particle particle;
	particle.direction = glm::vec3(model * glm::vec4(start_dir, 1.0f));
	if (particle.direction.x > 0) {
		particle.direction.x *= -1;
	}
	else if (particle.direction.x >= 0) {
		glm::mat4 rotate = glm::mat4(1.0f);
		rotate = glm::rotate(rotate, glm::radians(15.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		particle.direction = glm::vec3(rotate * glm::vec4(particle.direction, 1.0f));
	}
	particle.last_time = (int)cur_time;
	particle.life_time = start_life_time;
	particle.angle = 0.0f;
	particle.rotation_speed = start_rotation_speed;
	particle.pos = spawn_pos;
	particle.velocity = smoke_velocity;
	particle.mesh.Init(&particle_vert[0], 6 * 6, 6);

	particles.push_back(particle);

	last_particle_time = (int)cur_time;
}

void ParticleSystem::Update(glm::vec3 spawn_pos, glm::mat4 model) {
	int cur_time = SDL_GetTicks();
	for (int i = 0; i < particles.size(); ++i) {
		particles[i].life_time -= (cur_time - particles[i].last_time);
		if (particles[i].life_time <= 0)
			continue;
		particles[i].pos += ((float)(cur_time - particles[i].last_time) / 1000.0f) * particles[i].velocity * particles[i].direction;
		particles[i].angle += ((float)(cur_time - particles[i].last_time) / 1000.0f) * particles[i].rotation_speed;
		particles[i].last_time = cur_time;
	}

	int j = 0;
	while (j < particles.size()) {
		if (particles[j].life_time <= 0) {
			particles.erase(particles.begin() + j);
		}
		else {
			++j;
		}
	}

	if (cur_time - last_particle_time >= smoke_del_time) {
		Emmit(cur_time, spawn_pos, model);
	}

	Draw();
}

void ParticleSystem::Draw() {
	particle_shader.bind();

	for (int i = 0; i < particles.size(); ++i) {
		glm::mat4 part_model = glm::mat4(1.0f);
		float s = (float)particles[i].life_time / (float)start_life_time;
		part_model = glm::translate(part_model, particles[i].pos);
		part_model = glm::rotate(part_model, glm::radians(particles[i].angle), glm::vec3(0.0f, 0.0f, 1.0f));
		part_model = glm::scale(part_model, glm::vec3(s, s, s));
		particle_shader.SendMatrices(part_model, glm::mat4(1.0f), glm::mat4(1.0f));
		particles[i].mesh.DrawMesh();
	}
}