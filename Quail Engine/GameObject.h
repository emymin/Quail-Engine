#pragma once
#include "Mesh.h"
#include "Transform.h"
class GameObject
{
public:
	std::string name;
	std::vector<Mesh> meshes;
	Transform transform;
	GameObject(std::string name): name(name) {}
	GameObject(std::vector<Mesh> meshes,std::string name) : meshes(meshes),name(name) {}
	GameObject(Mesh mesh,std::string name) : meshes({ mesh }), name(name) {}
};

