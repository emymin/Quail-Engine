#include "VRDemo.h"

void VRDemo::OnInitialize()
{
	Texture* nekoTexture = Texture::Create("./Examples/Assets/Textures/neko.png", false);
	Texture* skytexture = Texture::Create("./Examples/Assets/Textures/skybox.hdr", true, false);

	PointLight* light = new PointLight(glm::vec3(1), 10, glm::vec3(1, 1, 1));
	Engine::Scene()->pointLights.push_back(light);

	Engine::Scene()->skybox = new Skybox(skytexture);

	GameObject* cube = Engine::Scene()->CreateGameObject("cube", Mesh::Cube());
	cube->transform.localPosition.z = 0;


	Material* cubemat = new Material(&Shader::StandardShader);
	cubemat->GetProperty<TextureProperty>("u_mainTexture")->texture = nekoTexture;
	cubemat->GetProperty<Float4Property>("u_mainColor")->value = glm::vec4(1);
	cube->meshes[0].material = cubemat;

}

void VRDemo::OnUpdate()
{
}

void VRDemo::OnGui()
{
}

void VRDemo::OnClose()
{
}

void VRDemo::OnKey(KeyEvent key)
{
}
