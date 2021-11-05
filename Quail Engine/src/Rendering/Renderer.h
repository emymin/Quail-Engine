#pragma once
#include "GLHeaders.h"
#include "Scene.h"

class Renderer {
private:
	void DrawSkybox(const Scene* scene) const;
public:
	void Clear() const;
	void Draw(const Scene* scene) const;
};