#include "OVRCamera.h"

glm::mat4 OVRCamera::GetProjectionMatrix() const
{
	return OpenVRApplication::leftProjectionMatrix;
}

void OVRCamera::SetAspectRatio(float width, float height)
{
}

glm::vec3 OVRCamera::GetPosition() const
{
	return OpenVRApplication::GetHeadset()->transform.WorldPosition();
}
