#include "Console.h"


void Console::Log(std::string text)
{
	print("[QUAIL ENGINE][LOG] : " + text);
}

void Console::Warning(std::string text)
{
	print("[QUAIL ENGINE][WARNING] : " + text);

}

void Console::Error(std::string text)
{
	print("[QUAIL ENGINE][ERROR] : " + text);
}
