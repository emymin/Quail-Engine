#include "Camera.h"

glm::mat4 Camera::GetViewMatrix() const
{
	glm::mat4 identity = glm::mat4(1.0f);
	glm::mat4 translation = glm::translate(identity, transform.localPosition);
	glm::mat4 rotation = glm::toMat4(transform.localRotation);
	return glm::inverse(translation * rotation);
}
