#pragma once
#include "GameTime.h"
#include "Engine.h"

class Engine;

class Game
{
public:
	std::string name;
	virtual void OnInitialize()=0;
	virtual void OnUpdate() = 0;
	virtual void OnGui() = 0;
	virtual void OnClose() = 0;
};

