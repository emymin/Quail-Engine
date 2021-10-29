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
