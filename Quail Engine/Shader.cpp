#include "Shader.h"

void DebugShaderCompilation(const unsigned int shader) {
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(sizeof(char) * length);
		glGetShaderInfoLog(shader, length, &length, message);
		std::cout << "Shader compilation error\n" << message << std::endl;
	}
}

unsigned int CompileShader(const char* source, const unsigned int type) {
	unsigned int shader;
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	DebugShaderCompilation(shader);
	return shader;
}

unsigned int CreateShaderProgram(const unsigned int vertexShader, const unsigned int fragmentShader, bool deleteShaders) {
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	if (deleteShaders) {
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	return shaderProgram;
}

unsigned int CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) {
	const char* vsSource = vertexShaderSource.c_str();
	const char* fsSource = fragmentShaderSource.c_str();

	unsigned int vertexShader = CompileShader(vsSource, GL_VERTEX_SHADER);
	unsigned int fragmentShader = CompileShader(fsSource, GL_FRAGMENT_SHADER);


	return CreateShaderProgram(vertexShader, fragmentShader, true);
}
