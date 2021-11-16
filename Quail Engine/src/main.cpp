#include "Engine.h"

#include "../Examples/Demo1/ExampleGame.h" //1
#include "../Examples/Demo2/Demo2.h" //2
#include "../Examples/VRDemo/VRDemo.h" //3
#include "EngineUI.h"

#define DEMO 3

int main() {

	Engine engine("Quail Engine Test");

#if DEMO == 1
	ExampleGame game;
	EngineUI ui;
	engine.Initialize(1000,1000);
#endif
#if DEMO == 2
	Demo2 game;
	EngineUI ui;
	engine.Initialize(1000, 1000);
#endif
#if DEMO == 3
	VRDemo game;
	EngineUI ui;
	OpenVRApplication::Initialize();
	engine.Initialize<OpenVRRenderer>(1000, 1000,false); //WaitGetPoses wastes a lot of time if VSync is enabled

#endif

	float lastTime = 0;
	while (!engine.ShouldClose()) {
		engine.Update();
	}
	engine.Destroy();

	return 0;
}