#include "Scene.h"

GameObject* Scene::Add(GameObject object)
{
	m_gameObjects[object.m_Name] = object;
	return &(m_gameObjects[object.m_Name]);
}

GameObject* Scene::CreateGameObject(std::string name, std::vector<Mesh> meshes)
{
	GameObject gameObject;
	gameObject.m_Name = name;
	gameObject.meshes = meshes;
	return Add(gameObject);
	
}

GameObject* Scene::Get(std::string name)
{
	return &(m_gameObjects[name]);
}

void Scene::Rename(GameObject* gameObject, std::string name)
{
	if (m_gameObjects.find(name) == m_gameObjects.end()) { return; }
	gameObject->m_Name = name;
}

