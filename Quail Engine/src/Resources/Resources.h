#pragma once
#include <iostream>
class Resources
{
private:
	static void Initialize();
public:
	friend class Engine;
};

