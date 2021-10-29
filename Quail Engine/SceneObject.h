#pragma once
#include "Mesh.h"
#include "Transform.h"
class GameObject
{
public:
	std::vector<Mesh> meshes;
	Transform transform;
	GameObject(std::vector<Mesh> meshes) : meshes(meshes) {}
	GameObject(Mesh mesh) : meshes({ mesh }) {}
};

