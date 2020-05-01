#include "Display.h"
#include "Player.h"
#include "Field.h"

int main(int argc, char** argv) {
	SDL_Event Event;
	std::string title = "flappybird";
	int width = 800;
	int height = 600;

	Display display(width, height, title);
	Player player;
	Field field;
	player.Init(width, height);
	field.Init();

	unsigned int last_time;
	unsigned int cur_time;

	cur_time = SDL_GetTicks();
	last_time = cur_time;

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
		display.Swap();
		last_time = cur_time;
	}

	player.ShatUp();
	field.ShatUp();

	return 0;
}