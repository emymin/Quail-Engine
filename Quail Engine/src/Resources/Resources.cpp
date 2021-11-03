#include "Resources.h"
#include "Console.h"
#include "Shader.h"
#include "Texture.h"


void Resources::Initialize()
{
	std::string basicFragment =
#include "Resources/Shaders/basicFragment.glsl"
		;
	std::string basicVertex =
#include "Resources/Shaders/basicVertex.glsl"
		;
	std::string standardFragment =
#include "Resources/Shaders/standardFragment.glsl"
		;
	std::string skyboxVertex =
#include "Resources/Shaders/skyboxVertex.glsl"
		;
	
	Shader::BasicShader = Shader(basicFragment, basicVertex);
	Shader::BasicShader.Compile();
	Shader::StandardShader = Shader(standardFragment, basicVertex);
	Shader::StandardShader.Compile();
	Shader::SkyboxShader = Shader(basicFragment,skyboxVertex);
	Shader::SkyboxShader.Compile();
	unsigned char whiteBuffer[4] = { 255,255,255,255 };
	Texture::White = Texture(whiteBuffer, 1, 1);
}

