#pragma once
#include "Transform.h"
class Camera
{
private:
	glm::mat4 m_projectionMatrix;
public:
	Transform transform;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetViewProjectionMatrix() const { return m_projectionMatrix * GetViewMatrix(); }

};

