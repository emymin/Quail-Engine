#include "Engine.h"

#include "../Examples/Demo1/ExampleGame.h"
#include "../Examples/Demo2/Demo2.h"



int main() {

	Demo2 game;
	Engine engine(&game);
	
	engine.Initialize(1000,1000);

	float lastTime = 0;
	while (!engine.ShouldClose()) {
		engine.Update();
	}
	engine.Destroy();

	return 0;
}