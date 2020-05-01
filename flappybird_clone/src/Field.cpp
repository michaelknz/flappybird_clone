#include "Field.h"

Field::Field() {

}

Field::~Field() {

}

void Field::Init() {
	
	SetVerticesDefault();

	velocity = 0.3f;
	dist = 0.8f;

	field_shader.Init("obstacle", "NULL");
	float i = 0.0f;
	while (i <= (2.0f+dist)){
		Obstacle ob;
		std::vector<float> cur_vertices_up;
		std::vector<float> cur_vertices_down;
		float del_value = RandFloat(0.4f);
		cur_vertices_up = SetVerticesUp(del_value);
		cur_vertices_down = SetVerticesDown(del_value);
		ob.up.Init(&cur_vertices_up[0], 6 * 6, 6);
		ob.down.Init(&cur_vertices_down[0], 6 * 6, 6);
		ob.pos = glm::vec3(i, 0.0f, 0.0f);
		obstacles.push_back(ob);
		i += dist;
	}
}

void Field::Draw() {
	field_shader.bind();
	for (unsigned int i = 0; i < obstacles.size(); ++i) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, obstacles[i].pos);
		field_shader.SendMatrices(model, glm::mat4(1.0f), glm::mat4(1.0f));
		obstacles[i].up.DrawMesh();
		obstacles[i].down.DrawMesh();
	}
}

void Field::CheckIsOut() {
	if (obstacles[0].pos.x <= -2.0f) {
		obstacles[0].up.ShatUp();
		obstacles[0].down.ShatUp();
		obstacles.erase(obstacles.begin());
		Obstacle ob;
		std::vector<float> cur_vertices_up;
		std::vector<float> cur_vertices_down;
		float del_value = RandFloat(0.4f);
		cur_vertices_up = SetVerticesUp(del_value);
		cur_vertices_down = SetVerticesDown(del_value);
		ob.up.Init(&cur_vertices_up[0], 6 * 6, 6);
		ob.down.Init(&cur_vertices_down[0], 6 * 6, 6);
		ob.pos = (*(obstacles.end() - 1)).pos;
		ob.pos.x += dist;
		obstacles.push_back(ob);
	}
}

void Field::Update(unsigned int del_time) {
	CheckIsOut();
	for (int i = 0; i < obstacles.size(); ++i) {
		obstacles[i].pos.x -= velocity * (float)del_time / 1000.0f;
	}
}

float Field::RandFloat(float start) {
	srand(time(0));
	float dig = (float)(rand() % (int)(start * 1000.0f - 100.0f) + 100.0f) / 1000.0f;
	int sign = rand() % 3;
	if (sign % 2 != 0){
		dig = -1.0f * dig;
	}
	return dig;
}

std::vector<float> Field::SetVerticesUp(float del_value) {
	std::vector<float>output;
	output = vertices_up;
	output[6 + 1] += del_value;
	output[6 * 4 + 1] += del_value;
	output[6 * 5 + 1] += del_value;
	return output;
}

std::vector<float> Field::SetVerticesDown(float del_value) {
	std::vector<float>output;
	output = vertices_down;
	output[6 + 1] += del_value;
	output[6 * 4 + 1] += del_value;
	output[6 * 5 + 1] += del_value;
	return output;
}

void Field::SetVerticesDefault() {
	vertices_up = {
		0.9f,1.0f,0.0f,1.0f,1.0f,1.0f,
		0.9f,0.2f,0.0f,1.0f,1.0f,1.0f,
		1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
		1.0f,1.0f,0.0f,1.0f,1.0f,1.0f,
		1.0f,0.2f,0.0f,1.0f,1.0f,1.0f,
		0.9f,0.2f,0.0f,1.0f,1.0f,1.0f
	};

	vertices_down = {
		0.9f,-1.0f,0.0f,1.0f,1.0f,1.0f,
		0.9f,-0.2f,0.0f,1.0f,1.0f,1.0f,
		1.0f,-1.0f,0.0f,1.0f,1.0f,1.0f,
		1.0f,-1.0f,0.0f,1.0f,1.0f,1.0f,
		1.0f,-0.2f,0.0f,1.0f,1.0f,1.0f,
		0.9f,-0.2f,0.0f,1.0f,1.0f,1.0f
	};
}

void Field::ShatUp() {
	for (int i = 0; i < obstacles.size(); ++i) {
		obstacles[i].up.ShatUp();
		obstacles[i].down.ShatUp();
	}
	field_shader.ShatUp();
}