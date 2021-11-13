#pragma once
#include "Mesh.h"

class Skybox
{
private:
	Mesh m_Mesh;
	Material m_Material;
public:
	glm::vec3 ambientColor;
	float ambientStrength=0.3;
	Texture* texture;
	Skybox(Texture* texture);

	friend class Renderer;
	friend class Scene;
};

