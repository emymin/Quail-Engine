#pragma once
#include <iostream>
#include <glad/glad.h>
#include "Utils.h"

class Shader {
private:
	unsigned int m_RendererID;
	unsigned int m_FragmentID;
	unsigned int m_VertexID;

	const char* m_fragmentSource;
	const char* m_vertexSource;

	unsigned int GetUniformLocation(const std::string& name);
	bool DebugShaderCompilation(const unsigned int shader);
	unsigned int CompileShader(const char* source, const unsigned int type);
public:
	Shader(std::string& fragmentSource, std::string& vertexSource);
	~Shader();
	bool Compile();
	void Bind() const;
	void Unbind() const;
	void SetUniform4f(const std::string& name,float x,float y,float z,float w);
	void setUniform1i(const std::string& name, int value);
};