#include "Transform.h"
#include "Utils.h"
#include <algorithm>

void Transform::SetParent(Transform* transform)
{
	if (parent != nullptr) {
		parent->children.erase(std::find(parent->children.begin(), parent->children.end(), this));
	}
	this->parent = transform;
	if (transform != nullptr) {
		transform->children.push_back(this);
	}
}

Transform* Transform::GetParent() const
{
	return parent;
}

std::vector<Transform*> Transform::GetChildren() const
{
	return children;
}

glm::vec3 Transform::WorldPosition()
{
	return GetModelMatrix() * glm::vec4(localPosition,1);
}

glm::quat Transform::WorldRotation()
{
	return toQuat(GetModelMatrix());
}


glm::mat4 Transform::GetModelMatrix() const
{
	glm::mat4 local = GetLocalModelMatrix();
	Transform* current = this->parent;
	while (current != nullptr) {
		local = current->GetLocalModelMatrix()* local;
		current = current->parent;
	}
	return local;

}

glm::mat4 Transform::GetLocalModelMatrix() const
{
	glm::mat4 identity(1.0f);
	glm::mat4 scalation = glm::scale(identity, localScale);
	glm::mat4 rotation = glm::toMat4(localRotation);
	glm::mat4 translation = glm::translate(identity, localPosition);
	return translation * rotation * scalation;
}

glm::vec3 Transform::eulerAngles() const
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
	localRotation = rotation*localRotation;
}

glm::vec3 Transform::LocalDirection(glm::vec3 dir) const
{
	return normalize(glm::toMat4(localRotation)* glm::vec4(dir, 0));
}
