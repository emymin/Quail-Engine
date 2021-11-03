#include "Skybox.h"

Skybox::Skybox(Texture* texture) : m_Mesh(Mesh::Cube()),m_Material(&Shader::SkyboxShader),texture(texture)
{
	m_Mesh.material = &m_Material;
}
