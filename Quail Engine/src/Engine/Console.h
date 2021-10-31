#pragma once
#include <iostream>
#include <fmt/core.h>

class Console
{
private:
	static void print(std::string text) { std::cout << text << std::endl; }
public:
	static void Log(std::string text);
	static void Warning(std::string text);
	static void Error(std::string text);

};

