#pragma once
#include "GLHeaders.h"
class Transform
{
public:
	glm::vec3 localPosition;
	glm::vec3 localScale;
	glm::quat localRotation;
	Transform() : localPosition(0), localScale(1), localRotation(glm::vec3(0)) {}
	glm::mat4 GetModelMatrix() const;
	glm::vec3 eulerAngles();
	void SetRotation(glm::vec3 eulerAngles);
	void SetRotation(float x, float y, float z);
	void Rotate(float angle, glm::vec3 axis);

	glm::vec3 LocalDirection(glm::vec3 dir) const;
	glm::vec3 RotatePoint(glm::vec3 pos){ return GetModelMatrix() * glm::vec4(pos, 1); }

	glm::vec3 Up() const { return LocalDirection(glm::vec3(0, 1, 0)); }
	glm::vec3 Forward() const { return LocalDirection(glm::vec3(0, 0, 1)); }
	glm::vec3 Right() const { return LocalDirection(glm::vec3(1, 0, 0)); }
};

