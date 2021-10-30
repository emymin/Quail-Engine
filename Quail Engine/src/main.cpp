#include "Renderer.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Engine.h"

#include "../Examples/Demo1/ExampleGame.h"
#include "../Examples/Demo2/Demo2.h"

ExampleGame game;

Engine engine(&game);


int main() {
	engine.Initialize(1000,1000);

	float lastTime = 0;
	while (!engine.ShouldClose()) {
		engine.Update();
	}
	engine.Destroy();

	return 0;
}