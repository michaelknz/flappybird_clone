#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

void Player::Init() {

	vertices = {
		-0.035f, -0.075f, 0.0f, 0.0f, 0.0f,
		-0.035f, 0.075f, 0.0f, 0.0f, 1.0f,
		0.035f, -0.075f, 0.0f, 1.0f, 0.0f,
		-0.035f, 0.075f, 0.0f, 0.0f, 1.0f,
		0.035f, 0.075f, 0.0f, 1.0f, 1.0f,
		0.035f, -0.075f, 0.0f, 1.0f, 0.0f
	};

	player_quad.Init(&vertices[0], 6 * 5, 5);
	player_shader.Init("player_shader", "res/Ship.png");
}

void Player::Draw() {
	player_shader.bind();
	player_quad.DrawMesh();
}

void Player::ShatUp() {
	player_quad.ShatUp();
	player_shader.ShatUp();
}