#include "Shader.h"
#include "Console.h"
#include "Resources.h"

unsigned int Shader::GetUniformLocation(const std::string& name)
{
	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1) {
		//Console::Error(fmt::format("Uniform {} not found", name));
	}
	return location;
}

bool Shader::DebugShaderCompilation(const unsigned int shader)
{
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(sizeof(char) * length);
		glGetShaderInfoLog(shader, length, &length, message);
		Console::Error(fmt::format("Shader compilation error\n{}",message));
		return false;
	}
	return true;
}


Shader::Shader(const std::string& fragmentSource,const std::string& vertexSource)
{
	m_FragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	m_VertexID = glCreateShader(GL_VERTEX_SHADER);
	m_RendererID = glCreateProgram();

	m_fragmentSource = fragmentSource.c_str();
	m_vertexSource = vertexSource.c_str();


}

Shader::Shader()
{

}

/*Shader::~Shader()
{
	glDeleteShader(m_FragmentID);
	glDeleteShader(m_VertexID);
	glDeleteProgram(m_RendererID);
}*/

bool Shader::Compile()
{
	glShaderSource(m_FragmentID, 1, &m_fragmentSource, NULL);
	glCompileShader(m_FragmentID);
	if (!DebugShaderCompilation(m_FragmentID)) { return false; }

	glShaderSource(m_VertexID, 1, &m_vertexSource, NULL);
	glCompileShader(m_VertexID);
	if (!DebugShaderCompilation(m_VertexID)) { return false; }

	glAttachShader(m_RendererID, m_FragmentID);
	glAttachShader(m_RendererID, m_VertexID);
	glLinkProgram(m_RendererID);

	return true;

}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float x, float y, float z, float w)
{
	glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetUniform3f(const std::string& name, float x, float y, float z) {
	glUniform3f(GetUniformLocation(name), x, y, z);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);

}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4& matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformCount() const
{
	int count;
	glGetProgramiv(m_RendererID, GL_ACTIVE_UNIFORMS, &count);
	return count;
}


std::vector<UniformData> Shader::GetUniforms() const
{
	int uniformCount = GetUniformCount();
	std::vector<UniformData> uniforms(uniformCount);
	int length;
	int size;
	unsigned int type;
	for (int i = 0; i < uniformCount; i++)
	{
		char name[MAXIMUM_UNIFORM_NAME_LENGTH];
		UniformData uniform;
		glGetActiveUniform(m_RendererID, (GLuint)i,MAXIMUM_UNIFORM_NAME_LENGTH , &length, &size, &type, name);
		uniform.index = i;
		uniform.type = type;
		uniform.name = std::string(name);
		uniforms[i] = uniform;
	}
	return uniforms;

}



Shader Shader::BasicShader;

Shader Shader::StandardShader;

Shader Shader::SkyboxShader;
