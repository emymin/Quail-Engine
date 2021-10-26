#pragma once
#include <iostream>
#include <glad/glad.h>
#include "Utils.h"

void DebugShaderCompilation(const unsigned int shader);

unsigned int CompileShader(const char* source, const unsigned int type);

unsigned int CreateShaderProgram(const unsigned int vertexShader, const unsigned int fragmentShader, bool deleteShaders = false);

unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
