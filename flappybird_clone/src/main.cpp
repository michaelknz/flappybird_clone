#include "Display.h"
#include "Mesh.h"
#include "Shader.h"

int main(int argc, char** argv) {
	SDL_Event Event;
	std::string title = "flappybird";
	int width = 800;
	int height = 600;

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f
	};

	Display display(width, height, title);
	Shader shader("bshader");
	Mesh mesh(vertices, 6 * 3);

	while (true) {
		if (SDL_PollEvent(&Event)) {
			if (Event.type == SDL_QUIT) {
				break;
			}
		}

		display.Clean_Display(0.5f, 0.5f, 1.0f, 1.0f);
		shader.bind();
		mesh.DrawMesh();
		display.Swap();
	}

	return 0;
}