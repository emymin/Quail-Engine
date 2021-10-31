#include "Transform.h"

glm::mat4 Transform::GetModelMatrix() const
{
	glm::mat4 identity(1.0f);
	glm::mat4 scalation = glm::scale(identity, localScale);
	glm::mat4 rotation = glm::toMat4(localRotation);
	glm::mat4 translation = glm::translate(identity, localPosition);
	return translation*rotation*scalation;
}

glm::vec3 Transform::eulerAngles()
{
	return glm::eulerAngles(localRotation);
}

void Transform::SetRotation(glm::vec3 eulerAngles)
{
	localRotation = glm::quat(eulerAngles);
}

void Transform::SetRotation(float x, float y, float z)
{
	SetRotation(glm::vec3(x, y, z));
}

void Transform::Rotate(float angle, glm::vec3 axis)
{
	glm::quat rotation = glm::angleAxis(angle,axis);
	localRotation = localRotation*rotation;
}
