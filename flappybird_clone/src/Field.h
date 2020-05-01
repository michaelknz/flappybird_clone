#pragma once
#include "Mesh.h"
#include "Shader.h"
#include <vector>
#include <cstdlib>
#include <ctime>

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
	void ShatUp();
	void Draw();
	void Update(unsigned int del_time);
	void CheckIsOut();
	float RandFloat(float start);
	std::vector<float> SetVerticesUp(float del_value);
	std::vector<float> SetVerticesDown(float del_value);
	void SetVerticesDefault();
private:
	Shader field_shader;
	std::vector<float> vertices_up;
	std::vector<float> vertices_down;
	std::vector<Obstacle> obstacles;
	float velocity;
	float dist;
};

