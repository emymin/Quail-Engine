#pragma once
#include "Mesh.h"
#include "Transform.h"
class GameObject
{
public:
	std::vector<Mesh> meshes;
	Transform transform;
	std::string GetName() { return m_Name; }
private:	
	std::string m_Name;

	friend class Scene;
};

