#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <SDL.h>

class PhisicsEngine
{
public:
	PhisicsEngine();
	~PhisicsEngine();
	void Init(float m_speed, float accel, float y);
	void Jump();
	glm::mat4 CreateModel(unsigned int del_time);
	void Update(unsigned int del_time);
private:
	float max_speed;
	float acceleration;
	float cur_speed;
	float y_pos;
};

