#include "Display.h"
#include "Player.h"
#include "Field.h"
#include "ParticleSystem.h"

int main(int argc, char** argv) {
	SDL_Event Event;
	std::string title = "flappybird";
	int width = 800;
	int height = 600;

	Display display(width, height, title);
	Player player;
	Field field;
	ParticleSystem particle_system;
	player.Init(width, height);
	field.Init();

	unsigned int last_time;
	unsigned int cur_time;

	cur_time = SDL_GetTicks();
	last_time = cur_time;

	glm::vec3 spawn_pos_s = glm::vec3(player.GetPlayerVert()[0], player.GetPlayerVert()[1], player.GetPlayerVert()[2]);

	particle_system.Init(spawn_pos_s, player.GetModel());

	while (true) {
		if (SDL_PollEvent(&Event)) {
			if (Event.type == SDL_QUIT) {
				break;
			}

			if (Event.type == SDL_KEYDOWN) {
				if (Event.key.keysym.sym == SDLK_SPACE) {
					player.Jump();
				}
			}
		}

		display.Clean_Display(0.5f, 0.5f, 1.0f, 1.0f);
		cur_time = SDL_GetTicks();
		player.Update(cur_time - last_time);
		player.Draw();
		field.Draw();
		field.Update(cur_time - last_time);

		glm::mat4 cur_model = glm::mat4(1.0f);
		cur_model = glm::translate(cur_model, glm::vec3(0.0f, player.GetPhisics().GetPos(), 0.0f));
		cur_model = glm::rotate(cur_model, glm::radians(player.GetPhisics().GetAngle()), glm::vec3(0.0f, 0.0f, 1.0f));
		glm::vec3 cur_spawn_pos_s = glm::vec3(cur_model * glm::vec4(spawn_pos_s, 1.0f));
		particle_system.Update(cur_spawn_pos_s, player.GetModel());

		display.Swap();
		if (PhisicsEngine::CoolisionDetection(field.GetObstacles(), player.GetPlayerVert(), player.GetModel(), player.GetView(), player.GetProjection())) {
			break;
		}
		last_time = cur_time;
	}

	player.ShatUp();
	field.ShatUp();

	return 0;
}