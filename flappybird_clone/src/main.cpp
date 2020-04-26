#include "Display.h"

int main(int argc, char** argv) {
	SDL_Event Event;
	std::string title = "flappybird";
	int width = 800;
	int height = 600;

	Display display(width, height, title);

	while (true) {
		if (SDL_PollEvent(&Event)) {
			if (Event.type == SDL_QUIT) {
				break;
			}
		}

		display.Clean_Display(0.5f, 0.5f, 1.0f, 1.0f);
		display.Swap();
	}

	return 0;
}