#pragma once
#include "Mesh.h"

class Skybox
{
private:
	Mesh m_Mesh;
	Material m_Material;
	Texture m_Texture;
public:
	Skybox(Texture& texture);
};

