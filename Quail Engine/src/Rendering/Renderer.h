#pragma once
#include "GLHeaders.h"
#include "Scene.h"


enum class RendererType {
	DesktopRenderer,
	VRRenderer
};

class Renderer {
public:
	virtual void Clear() const = 0;
	virtual void Draw(const Scene* scene) const = 0;
};
