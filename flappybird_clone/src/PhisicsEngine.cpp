#include "PhisicsEngine.h"

PhisicsEngine::PhisicsEngine() {

}

PhisicsEngine::~PhisicsEngine() {

}

void PhisicsEngine::Init(float m_speed, float accel, float y) {
	max_speed = m_speed;
	acceleration = accel;
	cur_speed = max_speed;
	y_pos = y;
}

void PhisicsEngine::Jump() {
	cur_speed = max_speed;
}

void PhisicsEngine::Update(unsigned int del_time) {
	cur_speed -= acceleration * ((float)del_time / 1000.0f);
}

glm::mat4 PhisicsEngine::CreateModel(unsigned int del_time) {
	y_pos += cur_speed * (float(del_time) / 1000.0f);
	if (y_pos <= -0.8f) {
		y_pos = -0.8f;
	}
	if (y_pos >= 0.8f) {
		y_pos = 0.8f;
	}
	float angle = 90.0f * (cur_speed / max_speed);
	last_angle = angle;
	if (angle <= -90.0f) {
		angle = -90.0f;
	}
	if (angle >= 90.0f) {
		angle = 90.0f;
	}
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, glm::vec3(0.0f, y_pos, 0.0f));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

	return model;
}

bool PhisicsEngine::CoolisionDetection(std::vector<Obstacle> obstacles, std::vector<float> player_vert, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {

	glm::vec4 ndc_player[4];

	ndc_player[0] = model * glm::vec4(player_vert[5 * 2], player_vert[5 * 2 + 1], player_vert[5 * 2 + 2], 1.0f);
	ndc_player[1] = model * glm::vec4(player_vert[5 * 4], player_vert[5 * 4 + 1], player_vert[5 * 4 + 2], 1.0f);
	ndc_player[2] = model * glm::vec4(player_vert[5 * 3], player_vert[5 * 3 + 1], player_vert[5 * 3 + 2], 1.0f);
	ndc_player[3] = model * glm::vec4(player_vert[0], player_vert[1], player_vert[2], 1.0f);

	for (int i = 0; i < obstacles.size(); ++i) {
		glm::vec4 ndc_up_obstacle[4];
		glm::vec4 ndc_down_obstacle[4];
		glm::mat4 ob_model_up = glm::mat4(1.0f);
		glm::mat4 ob_model_down = glm::mat4(1.0f);
		ob_model_up = glm::translate(ob_model_up, obstacles[i].pos);
		ob_model_down = glm::translate(ob_model_down, obstacles[i].pos);

		ndc_up_obstacle[0] = ob_model_up * glm::vec4(obstacles[i].vertices_up[6 * 4], obstacles[i].vertices_up[6 * 4 + 1], obstacles[i].vertices_up[6 * 4 + 2], 1.0f);
		ndc_up_obstacle[1] = ob_model_up * glm::vec4(obstacles[i].vertices_up[6 * 3], obstacles[i].vertices_up[6 * 3 + 1], obstacles[i].vertices_up[6 * 3 + 2], 1.0f);
		ndc_up_obstacle[2] = ob_model_up * glm::vec4(obstacles[i].vertices_up[0], obstacles[i].vertices_up[1], obstacles[i].vertices_up[2], 1.0f);
		ndc_up_obstacle[3] = ob_model_up * glm::vec4(obstacles[i].vertices_up[6], obstacles[i].vertices_up[6 + 1], obstacles[i].vertices_up[6 + 2], 1.0f);

		ndc_down_obstacle[0] = ob_model_down * glm::vec4(obstacles[i].vertices_down[6 * 3], obstacles[i].vertices_down[6 * 3 + 1], obstacles[i].vertices_down[6 * 3 + 2], 1.0f);
		ndc_down_obstacle[1] = ob_model_down * glm::vec4(obstacles[i].vertices_down[6 * 4], obstacles[i].vertices_down[6 * 4 + 1], obstacles[i].vertices_down[6 * 4 + 2], 1.0f);
		ndc_down_obstacle[2] = ob_model_down * glm::vec4(obstacles[i].vertices_down[6 * 5], obstacles[i].vertices_down[6 * 5 + 1], obstacles[i].vertices_down[6 * 5 + 2], 1.0f);
		ndc_down_obstacle[3] = ob_model_down * glm::vec4(obstacles[i].vertices_down[0], obstacles[i].vertices_down[1], obstacles[i].vertices_down[2], 1.0f);

		for (int j = 0; j < 4; ++j) {
			float a = (ndc_player[j].x - ndc_up_obstacle[0].x) * (ndc_up_obstacle[1].y - ndc_up_obstacle[0].y) - (ndc_up_obstacle[1].x - ndc_up_obstacle[0].x) * (ndc_player[j].y - ndc_up_obstacle[0].y);
			float b = (ndc_player[j].x - ndc_up_obstacle[1].x) * (ndc_up_obstacle[2].y - ndc_up_obstacle[1].y) - (ndc_up_obstacle[2].x - ndc_up_obstacle[1].x) * (ndc_player[j].y - ndc_up_obstacle[1].y);
			float c = (ndc_player[j].x - ndc_up_obstacle[2].x) * (ndc_up_obstacle[3].y - ndc_up_obstacle[2].y) - (ndc_up_obstacle[3].x - ndc_up_obstacle[2].x) * (ndc_player[j].y - ndc_up_obstacle[2].y);
			float d = (ndc_player[j].x - ndc_up_obstacle[3].x) * (ndc_up_obstacle[0].y - ndc_up_obstacle[3].y) - (ndc_up_obstacle[0].x - ndc_up_obstacle[3].x) * (ndc_player[j].y - ndc_up_obstacle[3].y);

			if (((a < 0) == (b < 0) && (b < 0) == (c < 0) && (c < 0) == (d < 0) && (d < 0) == (a < 0)) || (a == 0) || (b == 0) || (c == 0) || (d == 0)) {
				return true;
			}
		}

		for (int j = 0; j < 4; ++j) {
			float a = (ndc_player[j].x - ndc_down_obstacle[0].x) * (ndc_down_obstacle[1].y - ndc_down_obstacle[0].y) - (ndc_down_obstacle[1].x - ndc_down_obstacle[0].x) * (ndc_player[j].y - ndc_down_obstacle[0].y);
			float b = (ndc_player[j].x - ndc_down_obstacle[1].x) * (ndc_down_obstacle[2].y - ndc_down_obstacle[1].y) - (ndc_down_obstacle[2].x - ndc_down_obstacle[1].x) * (ndc_player[j].y - ndc_down_obstacle[1].y);
			float c = (ndc_player[j].x - ndc_down_obstacle[2].x) * (ndc_down_obstacle[3].y - ndc_down_obstacle[2].y) - (ndc_down_obstacle[3].x - ndc_down_obstacle[2].x) * (ndc_player[j].y - ndc_down_obstacle[2].y);
			float d = (ndc_player[j].x - ndc_down_obstacle[3].x) * (ndc_down_obstacle[0].y - ndc_down_obstacle[3].y) - (ndc_down_obstacle[0].x - ndc_down_obstacle[3].x) * (ndc_player[j].y - ndc_down_obstacle[3].y);

			if (((a < 0) == (b < 0) && (b < 0) == (c < 0) && (c < 0) == (d < 0) && (d < 0) == (a < 0)) || (a == 0) || (b == 0) || (c == 0) || (d == 0)) {
				return true;
			}
		}
	}
	return false;
}

float PhisicsEngine::GetPos() {
	return y_pos;
}

float PhisicsEngine::GetAngle() {
	return last_angle;
}