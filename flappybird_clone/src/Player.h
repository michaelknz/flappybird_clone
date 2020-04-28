#pragma once
#include "Shader.h"
#include "Mesh.h"
#include <vector>
class Player
{
public:
	Player();
	~Player();
	void Init();
	void ShatUp();
	void Draw();
private:
	std::vector<float> vertices;
	Mesh player_quad;
	Shader player_shader;
};

