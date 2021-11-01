#include "Resources.h"
#include "Console.h"
#include "Shader.h"

std::string Resources::basicFragment;

std::string Resources::basicVertex;

void Resources::Initialize()
{
	basicFragment =
#include "Resources/Shaders/basicFragment.glsl"
		;
	basicVertex =
#include "Resources/Shaders/basicVertex.glsl"
		;
	Shader::BasicShader = Shader(basicFragment, basicVertex);
}

