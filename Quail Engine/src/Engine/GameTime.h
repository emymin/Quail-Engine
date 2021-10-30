#pragma once
#include "GLHeaders.h"
class GameTime
{
public:
	float currentTime;
	float deltaTime;
	float lastTime;
	float fps;
	static float GetTime() { return glfwGetTime(); }
};

