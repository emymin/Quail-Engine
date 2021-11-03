#include "Skybox.h"

Skybox::Skybox(Texture* texture) : m_Mesh(Mesh::Cube()),m_Material(&Shader::SkyboxShader),texture(nullptr)
{
	this->texture = texture;
	m_Mesh.material = &m_Material;
	m_Material.GetProperty<TextureProperty>("u_mainTexture")->texture = texture;
}
