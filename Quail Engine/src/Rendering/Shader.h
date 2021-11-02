#pragma once
#include "GLHeaders.h"
#include "Utils.h"
#include <vector>

#define MAXIMUM_UNIFORM_NAME_LENGTH 24

struct UniformData {
	int index;
	std::string name;
	unsigned int type;
};

class Shader {
private:
	unsigned int m_RendererID;
	unsigned int m_FragmentID;
	unsigned int m_VertexID;

	const char* m_fragmentSource;
	const char* m_vertexSource;

	unsigned int GetUniformLocation(const std::string& name);
	bool DebugShaderCompilation(const unsigned int shader);
	int GetUniformCount() const;

	Shader();
	
public:
	Shader(std::string& fragmentSource, std::string& vertexSource);
	//~Shader();
	bool Compile();
	void Bind() const;
	void Unbind() const;
	void SetUniform4f(const std::string& name,float x,float y,float z,float w);
	void SetUniform3f(const std::string& name, float x, float y, float z);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform1i(const std::string& name, int value);
	void SetUniformMat4f(const std::string& name, glm::mat4& matrix);
	std::vector<UniformData> GetUniforms() const;
	
	static Shader BasicShader;
	static Shader Standard;
	static Shader SkyboxShader;
	friend class Resources;
};