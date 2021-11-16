#pragma once
#include "Shader.h"
#include <iostream>
#include "GLHeaders.h"
#include "Transform.h"


class Light {
public:
	Transform transform;
private:
	virtual void Apply(Shader* shader, std::string uniformName) = 0;
};

class PointLight : public Light {
public:
	glm::vec3 col;
	float range;
	PointLight(glm::vec3 col = glm::vec3(0), float range = 0) :  col(col), range(range) {}
	static PointLight empty;
private:
	void Apply(Shader* shader, std::string uniformName) override;
	friend class Renderer;

};
