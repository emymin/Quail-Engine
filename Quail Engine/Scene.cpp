#include "Scene.h"

GameObject* Scene::Add(GameObject* object)
{
	gameObjects[object->name] = object;
	return (gameObjects[object->name]);
}

GameObject* Scene::Get(std::string name)
{
	return (gameObjects[name]);
}

void Scene::SetCamera(Camera* camera)
{
	this->camera = camera;
}
