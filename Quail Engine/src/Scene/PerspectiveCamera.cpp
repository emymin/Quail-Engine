#include "PerspectiveCamera.h"
void PerspectiveCamera::GenerateProjectionMatrix()
{
	m_projectionMatrix = glm::perspective(m_fov, m_aspect_ratio, m_near, m_far);
}

PerspectiveCamera::PerspectiveCamera(float fov, float aspect_ratio, float near, float far) : m_fov(fov), m_aspect_ratio(aspect_ratio), m_near(near), m_far(far)
{
	GenerateProjectionMatrix();
}


glm::mat4 PerspectiveCamera::GetProjectionMatrix() const
{
	return m_projectionMatrix;
}

void PerspectiveCamera::SetFOV(float value)
{
	m_fov = value;
	GenerateProjectionMatrix();
}

void PerspectiveCamera::SetAspectRatio(float width, float height)
{
	SetAspectRatio(width / height);
}

void PerspectiveCamera::SetAspectRatio(float value)
{
	m_aspect_ratio = value;
	GenerateProjectionMatrix();
}
