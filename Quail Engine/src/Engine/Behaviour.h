#pragma once
#include "Input.h"

class Behaviour
{
public:
	std::string name;
	Behaviour();
	virtual void OnInitialize()=0;
	virtual void OnUpdate() = 0;
	virtual void OnGui() = 0;
	virtual void OnClose() = 0;
	virtual void OnKey(KeyEvent key) = 0;
};

