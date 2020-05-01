#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <vector>

struct Obstacle {
	Mesh up;
	Mesh down;
	glm::vec3 pos;
};

class Field
{
public:
	Field();
	~Field();
	void Init();
	void Draw();
	void Update(unsigned int del_time);
	void CheckIsOut();
private:
	Shader field_shader;
	std::vector<float> vertices_up;
	std::vector<float> vertices_down;
	std::vector<Obstacle> obstacles;
	float velocity;
	float dist;
};

