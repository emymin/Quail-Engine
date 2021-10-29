#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"
struct IMaterialProperty {
	std::string name;
	IMaterialProperty(std::string& name) : name(name) {};
	virtual void Apply(Shader& shader) const = 0;
};

struct Float4Property : public IMaterialProperty {
	glm::vec4 value;
	Float4Property(std::string& name, glm::vec4 v=glm::vec4(0)) : value(v),IMaterialProperty(name) {}
	void Apply(Shader& shader) const override
	{
		shader.SetUniform4f(name,value.x, value.y, value.z, value.w);
	}

};

struct FloatProperty : public IMaterialProperty {
	float value;
	FloatProperty(std::string& name, float v = 0) : value(v), IMaterialProperty(name) {}
	void Apply(Shader& shader) const override
	{
		shader.SetUniform1f(name, value);
	}

};

struct TextureProperty : public IMaterialProperty {
	int slot;
	Texture* texture;
	TextureProperty(std::string& name,int slot = 0,Texture* texture = nullptr ) : slot(slot),texture(texture),IMaterialProperty(name) {}
	void Apply(Shader& shader) const override {
		if (texture != nullptr) {
			texture->Bind();
			shader.SetUniform1i(name, slot);
		}
	}

};