#include "Material.h"

Material::Material(Shader* shader) : shader(shader)
{	
	std::vector<UniformData> uniforms = shader->GetUniforms();
	for (UniformData& uniform : uniforms) {
		if (string_startswith(uniform.name, "material.")) {
			std::string propertyKey = uniform.name.substr(9, MAXIMUM_UNIFORM_NAME_LENGTH);
			switch (uniform.type) {
			case GL_FLOAT_VEC4: { m_Properties[propertyKey] = std::unique_ptr<Float4Property>(new Float4Property(uniform.name)); break; }
			case GL_FLOAT: {m_Properties[propertyKey] = std::unique_ptr<FloatProperty>(new FloatProperty(uniform.name)); break; }
			case GL_SAMPLER_2D: { m_Properties[propertyKey] = std::unique_ptr<TextureProperty>(new TextureProperty(uniform.name)); break; }

			default: {
				Console::Warning(fmt::format("Unsupported uniform type: {}", uniform.type));
			}
			}
		}
	}
}

void Material::ApplyUniforms() const
{
	for (auto& pair : m_Properties) {
		pair.second->Apply(*shader);
	}
}


