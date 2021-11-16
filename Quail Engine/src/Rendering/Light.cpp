#include "Light.h"

PointLight PointLight::empty = PointLight();

void PointLight::Apply(Shader* shader, std::string uniformName)
{
	shader->SetUniform1f(uniformName + ".range", range);
	shader->SetUniform3f(uniformName + ".pos", transform.WorldPosition());
	shader->SetUniform3f(uniformName + ".col", col);
}

