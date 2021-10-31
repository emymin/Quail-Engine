#include "Console.h"


const HANDLE Console::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Console::print(std::string text,TextColor color)
{
	bool colored = color != TextColor::DEFAULT;
	if (colored) {SetConsoleTextAttribute(hConsole, (int)color);}
	std::cout << text << std::endl;
	if (colored) {SetConsoleTextAttribute(hConsole, (int)TextColor::DEFAULT);}
}

void Console::Log(std::string text)
{
	print("[LOG] : " + text);
}

void Console::Warning(std::string text)
{
	print("[WARNING] : " + text, TextColor::YELLOW);

}

void Console::Error(std::string text)
{
	print("[ERROR] : " + text, TextColor::RED);
}
