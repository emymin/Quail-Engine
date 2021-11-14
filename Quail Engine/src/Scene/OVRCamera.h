#pragma once
#include "Camera.h"
#include "PerspectiveCamera.h"
class OVRCamera :
    public Camera
{
private:
	PerspectiveCamera leftCamera;
	PerspectiveCamera rightCamera;
	float m_IPD;
public:
	OVRCamera(float IPD);
	glm::mat4 GetProjectionMatrix() const override;
	glm::mat4 GetLeftProjectionMatrix()const;
	glm::mat4 GetRightProjectionMatrix()const;

	glm::mat4 GetLeftViewMatrix()const;
	glm::mat4 GetRightViewMatrix()const;


	void SetAspectRatio(float width, float height) override;

};

