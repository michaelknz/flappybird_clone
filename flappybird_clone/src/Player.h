#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "PhisicsEngine.h"
#include <vector>

class Player
{
public:
	Player();
	~Player();
	void Init(int width, int height);
	void ShatUp();
	void Draw();
	void Jump();
	void Update(unsigned int del_time);
	std::vector<float> GetPlayerVert();
	glm::mat4 GetModel();
	glm::mat4 GetView();
	glm::mat4 GetProjection();
private:
	std::vector<float> vertices;
	Mesh player_quad;
	Shader player_shader;
	PhisicsEngine phisics;
	glm::vec3 CameraPos;
	glm::vec3 CameraView;
	glm::vec3 CameraUp;
	glm::mat4 model_start;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	float start_y;
	float speed;
	float accseleration;
};

