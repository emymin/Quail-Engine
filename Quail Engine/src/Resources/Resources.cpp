#include "Resources.h"
#include "Console.h"
#include "Shader.h"
#include "Texture.h"


void Resources::Initialize()
{
	const std::string basicFragment =
#include <Shaders/basicFragment.glsl>
		;
	const std::string basicVertex =
#include <Shaders/basicVertex.glsl>
		;
	const std::string standardFragment =
#include <Shaders/standardFragment.glsl>
		;
	const std::string skyboxVertex =
#include <Shaders/skyboxVertex.glsl>
		;
	const std::string skyboxFragment =
#include <Shaders/skyboxFragment.glsl>
		;
	const std::string screenVertex =
#include <Shaders/screenVert.glsl>
		;
	const std::string screenFragment =
#include <Shaders/screenFrag.glsl>
		;
	
	Shader::BasicShader = Shader(basicFragment, basicVertex);
	Shader::BasicShader.Compile();
	Shader::StandardShader = Shader(standardFragment, basicVertex);
	Shader::StandardShader.Compile();
	Shader::SkyboxShader = Shader(skyboxFragment,skyboxVertex);
	Shader::SkyboxShader.Compile();
	Shader::ScreenShader = Shader(screenFragment, screenVertex);
	Shader::ScreenShader.Compile();

	unsigned char whiteBuffer[4] = { 255,255,255,255 };
	Texture::White = Texture(whiteBuffer, 1, 1);
}

