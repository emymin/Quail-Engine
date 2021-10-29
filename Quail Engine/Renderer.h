#pragma once
#include "GLHeaders.h"
#include "Camera.h"
#include "SceneObject.h"

class Renderer {
public:
	void Clear() const;
	void Draw(const GameObject& object,Camera& camera);

};