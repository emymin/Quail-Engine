#pragma once
#include "Mesh.h"
#include "Transform.h"
class SceneObject
{
public:
	std::vector<Mesh> meshes;
	Transform transform;
	SceneObject(std::vector<Mesh> meshes) : meshes(meshes) {}
	SceneObject(Mesh mesh) : meshes({ mesh }) {}
};

