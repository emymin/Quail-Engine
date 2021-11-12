#include "Engine.h"

#include "../Examples/Demo1/ExampleGame.h"
#include "../Examples/Demo2/Demo2.h"
#include "../Examples/VRDemo/VRDemo.h"
#include "EngineUI.h"



int main() {

	Engine engine("Quail Engine Test");
	VRDemo game;
	EngineUI ui;
	
	engine.Initialize(1000,1000);

	float lastTime = 0;
	while (!engine.ShouldClose()) {
		engine.Update();
	}
	engine.Destroy();

	return 0;
}