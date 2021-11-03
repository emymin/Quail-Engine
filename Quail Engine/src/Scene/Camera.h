#pragma once
#include "Transform.h"

class Camera
{
public:
	Transform transform;
	virtual glm::mat4 GetProjectionMatrix() const = 0;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetViewProjectionMatrix() const { return GetProjectionMatrix() * GetViewMatrix(); }
	virtual void SetAspectRatio(float width, float height) = 0;

};

class PerspectiveCamera :public Camera {
private:
	glm::mat4 m_projectionMatrix;
	void GenerateProjectionMatrix();
	float m_fov;
	float m_near;
	float m_far;
	float m_aspect_ratio;
public:
	PerspectiveCamera(float fov = PI/2.f, float aspect_ratio = 1.f, float near = 0.1f, float far = 500.f);
	glm::mat4 GetProjectionMatrix() const override;
	void SetFOV(float value);
	void SetAspectRatio(float value);
	virtual void SetAspectRatio(float width, float height) override;


};
