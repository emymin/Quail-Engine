#pragma once
#include <iostream>
class Resources
{
private:
	static void Initialize();
public:
	static std::string basicFragment;
	static std::string basicVertex;

	friend class Engine;
};

