#pragma once
#include "Mesh.h"

class Skybox
{
private:
	Mesh m_Mesh;
	Material m_Material;
public:
	Texture* texture;
	Skybox(Texture* texture);

	friend class Renderer;
	friend class Scene;
};

