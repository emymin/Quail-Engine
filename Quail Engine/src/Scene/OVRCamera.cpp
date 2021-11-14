#include "OVRCamera.h"

OVRCamera::OVRCamera(float IPD) : m_IPD(IPD)
{
	leftCamera.transform.SetParent(&transform);
	rightCamera.transform.SetParent(&transform);
	leftCamera.transform.localPosition.x = m_IPD * -0.5;
	rightCamera.transform.localPosition.x = m_IPD * 0.5;
}

glm::mat4 OVRCamera::GetProjectionMatrix() const
{
	return GetLeftProjectionMatrix();
}

glm::mat4 OVRCamera::GetLeftProjectionMatrix() const
{
	return leftCamera.GetProjectionMatrix();
}

glm::mat4 OVRCamera::GetRightProjectionMatrix() const
{
	return rightCamera.GetProjectionMatrix();
}

glm::mat4 OVRCamera::GetLeftViewMatrix() const
{
	return leftCamera.GetViewMatrix();
}

glm::mat4 OVRCamera::GetRightViewMatrix() const
{
	return rightCamera.GetViewMatrix();
}

void OVRCamera::SetAspectRatio(float width, float height)
{
}
