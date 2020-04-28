#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

void Player::Init() {

	vertices = {
		-0.3f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.3f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.3f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.3f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.3f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.3f, -0.5f, 0.0f, 1.0f, 0.0f
	};

	player_quad.Init(&vertices[0], 6 * 5, 5);
	player_shader.Init("player_shader");
}

void Player::Draw() {
	player_shader.bind();
	player_quad.DrawMesh();
}

void Player::ShatUp() {
	player_quad.ShatUp();
	player_shader.ShatUp();
}