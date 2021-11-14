#pragma once
#include "Transform.h"

class Camera
{
public:
	Transform transform;
	virtual glm::mat4 GetProjectionMatrix() const = 0;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetViewProjectionMatrix() const { return GetProjectionMatrix() * GetViewMatrix(); }
	virtual void SetAspectRatio(float width, float height) = 0;

};
