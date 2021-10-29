#pragma once
#include "GLHeaders.h"
#include "SceneObject.h"

class Renderer {
private:
	glm::mat4 m_viewProjection;
public:
	Renderer() : m_viewProjection(1.0f) {}
	void Clear() const;
	void Draw(const SceneObject object);
	void SetViewProjection(glm::mat4 viewProj) {
		m_viewProjection = viewProj;
	}
};