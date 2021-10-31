#pragma once
#include "Input.h"

class Game
{
public:
	std::string name;
	virtual void OnInitialize()=0;
	virtual void OnUpdate() = 0;
	virtual void OnGui() = 0;
	virtual void OnClose() = 0;
	virtual void OnKey(KeyEvent key) = 0;
};

