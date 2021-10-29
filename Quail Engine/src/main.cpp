#include "Renderer.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine.h"


Engine engine;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	engine.SetResolution(width, height);
}



int main() {
	engine.Initialize();

	float lastTime = 0;
	while (!engine.ShouldClose()) {
		engine.Update();
	}
	engine.Destroy();

	return 0;
}