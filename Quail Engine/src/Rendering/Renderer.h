#pragma once
#include "GLHeaders.h"
#include "Scene.h"

class Renderer {
public:
	void Clear() const;
	void Draw(const GameObject* object,Camera* camera);
	void Draw(const Scene* scene);
};