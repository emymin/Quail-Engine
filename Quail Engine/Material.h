#pragma once
#include <iostream>
#include <unordered_map>
#include "MaterialProperty.h"

class Material
{
private:
	std::unordered_map<std::string, std::unique_ptr<IMaterialProperty>> m_Properties;
public:
	Shader* shader;
	Material(Shader& shader);
	void ApplyUniforms() const;
	
	template <typename t>
	t* GetProperty(std::string name) { return dynamic_cast<t*>( &(*(m_Properties[name])) ); }

};

