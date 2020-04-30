#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

void Player::Init(int width, int height) {

	vertices = {
		-0.035f, -0.075f, 0.0f, 0.0f, 0.0f,
		-0.035f, 0.075f, 0.0f, 0.0f, 1.0f,
		0.035f, -0.075f, 0.0f, 1.0f, 0.0f,
		-0.035f, 0.075f, 0.0f, 0.0f, 1.0f,
		0.035f, 0.075f, 0.0f, 1.0f, 1.0f,
		0.035f, -0.075f, 0.0f, 1.0f, 0.0f
	};

	speed = 2.5f;
	accseleration = 8.0f;
	start_y = 0;

	player_quad.Init(&vertices[0], 6 * 5, 5);
	player_shader.Init("player_shader", "res/Ship.png");
	phisics.Init(speed, accseleration, start_y);

	model_start = glm::mat4(1.0f);
	model = glm::mat4(1.0f);
	view = glm::mat4(1.0f);
	projection = glm::mat4(1.0f);

	CameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
	CameraView = glm::vec3(0.0f, 0.0f, -1.0f);
	CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	model_start = glm::rotate(model_start, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	view = glm::lookAt(CameraPos, CameraPos + CameraView, CameraUp);
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	player_shader.bind();
	player_shader.SendMatrices(model_start, view, projection);
}

void Player::Draw() {
	player_shader.bind();
	player_quad.DrawMesh();
}

void Player::ShatUp() {
	player_quad.ShatUp();
	player_shader.ShatUp();
}

void Player::Jump() {
	phisics.Jump();
}

void Player::Update(unsigned int del_time) {
	phisics.Update(del_time);
	model = phisics.CreateModel(del_time);
	player_shader.bind();
	player_shader.SendMatrices(model * model_start, view, projection);
}