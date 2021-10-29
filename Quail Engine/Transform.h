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
};

