#pragma once
#include <unordered_map>
#include "GameObject.h"
#include "Camera.h"
class Scene
{
public:
	std::unordered_map<std::string,GameObject*> gameObjects;
	Camera* camera;
	GameObject* Add(GameObject* object);
	GameObject* Get(std::string name);
	void SetCamera(Camera* camera);
};

