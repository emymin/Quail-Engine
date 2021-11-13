#pragma once
#include "Shader.h"
#include <iostream>
#include "GLHeaders.h"


class Light {
private:
	virtual void Apply(Shader* shader, std::string uniformName) = 0;
};

class PointLight : Light {
public:
	glm::vec3 pos;
	glm::vec3 col;
	float range;
	PointLight(glm::vec3 col = glm::vec3(0), float range = 0, glm::vec3 pos = glm::vec3(0)) : pos(pos), col(col), range(range) {}
	static PointLight empty;
private:
	void Apply(Shader* shader, std::string uniformName) override;
	friend class Renderer;

};
