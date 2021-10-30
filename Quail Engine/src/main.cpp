#include "Renderer.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine.h"

#include "../Examples/Demo1/ExampleGame.h"
#include "../Examples/Demo2/Demo2.h"

Engine engine;
ExampleGame game;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	engine.SetResolution(width, height);
}



int main() {
	engine.Initialize(&game);

	float lastTime = 0;
	while (!engine.ShouldClose()) {
		engine.Update();
	}
	engine.Destroy();

	return 0;
}