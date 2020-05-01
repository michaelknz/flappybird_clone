#include "Field.h"

Field::Field() {

}

Field::~Field() {

}

void Field::Init() {
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

	velocity = 0.5f;
	dist = 0.3f;

	field_shader.Init("obstacle", "NULL");
	float i = 0.0f;
	while (i <= (2.0f+dist)){
		Obstacle ob;
		ob.up.Init(&vertices_up[0], 6 * 6, 6);
		ob.down.Init(&vertices_down[0], 6 * 6, 6);
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
		obstacles.erase(obstacles.begin());
		Obstacle ob;
		ob.up.Init(&vertices_up[0], 6 * 6, 6);
		ob.down.Init(&vertices_down[0], 6 * 6, 6);
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