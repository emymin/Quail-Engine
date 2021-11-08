#pragma once

#include <fstream>
#include <sstream>
#include <algorithm>
#include "Console.h"

#if _DEBUG
#define ASSERT(x) if(!x)__debugbreak();
#else
#define ASSERT(x) x
#endif

static std::string ReadTextFromFile(std::string filePath) {
	std::string text;
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(filePath);
		std::stringstream fileStream;
		fileStream << file.rdbuf();
		file.close();
		text = fileStream.str();
	}
	catch (std::ifstream::failure e) {
		Console::Error("Error reading file " + filePath);
	}
	return text;
}

static inline std::string string_replace(const std::string& in, const std::string& from, const std::string& to) {
	std::string newString(in);
	return newString.replace(newString.find(from), sizeof(from) - 1, to);
}

static inline bool string_startswith(const std::string& in, const std::string& prefix) {
	if (in.length() < prefix.length()) { return false; }
	return std::mismatch(prefix.begin(), prefix.end(), in.begin()).first == prefix.end();
}

static inline std::string find_directory_of_path(const std::string& fname)
{
	size_t pos = fname.find_last_of("\\/");
	return (std::string::npos == pos)
		? ""
		: fname.substr(0, pos);
}

class NotImplementedException : public std::logic_error
{
public:
	NotImplementedException() : std::logic_error("Feature not yet implemented") { };
};