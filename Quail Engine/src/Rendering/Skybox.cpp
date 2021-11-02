#include "Skybox.h"

Skybox::Skybox(Texture& texture) : m_Mesh(Mesh::Cube()),m_Material(&Shader::BasicShader),m_Texture(texture)
{

}
