#pragma once
#include <unordered_map>
#include "GameObject.h"
#include "Camera.h"
class Scene
{
private:
	GameObject* Add(GameObject object);
	std::unordered_map<std::string,GameObject> m_gameObjects;
public:
	Camera* camera;
	GameObject* CreateGameObject(std::string name, std::vector<Mesh> meshes);
	GameObject* CreateGameObject(std::string name, Mesh mesh) { CreateGameObject(name, { mesh }); }
	GameObject* Get(std::string name);
	void Rename(GameObject* gameObject, std::string name);

	friend class Renderer;
	friend class Application;

};

