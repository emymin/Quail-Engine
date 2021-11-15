#pragma once
#include "Camera.h"
#include "OpenVRApplication.h"

class OVRCamera :
    public Camera
{

public:
	glm::mat4 GetProjectionMatrix() const override;


	void SetAspectRatio(float width, float height) override;


	glm::vec3 GetPosition() const override;

};

