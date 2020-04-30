#include "PhisicsEngine.h"

PhisicsEngine::PhisicsEngine() {

}

PhisicsEngine::~PhisicsEngine() {

}

void PhisicsEngine::Init(float m_speed, float accel, float y) {
	max_speed = m_speed;
	acceleration = accel;
	cur_speed = max_speed;
	y_pos = y;
}

void PhisicsEngine::Jump() {
	cur_speed = max_speed;
}

void PhisicsEngine::Update(unsigned int del_time) {
	cur_speed -= acceleration * ((float)del_time / 1000.0f);
}

glm::mat4 PhisicsEngine::CreateModel(unsigned int del_time) {
	y_pos += cur_speed * (float(del_time) / 1000.0f);
	float angle = 90.0f * (cur_speed / max_speed);
	if (angle <= -90.0f) {
		angle = -90.0f;
	}
	if (angle >= 90.0f) {
		angle = 90.0f;
	}
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(0.0f, y_pos, 0.0f));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

	return model;
}