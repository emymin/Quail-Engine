#include "VRDemo.h"
#include "OVRCamera.h"

void VRDemo::OnInitialize()
{
	Texture* nekoTexture = Texture::Create("./Examples/Assets/Textures/neko.png", false);
	Texture* skytexture = Texture::Create("./Examples/Assets/Textures/skybox.hdr", true, false);

	PointLight* leftlight = new PointLight(glm::vec3(1), 1);
	leftlight->transform.SetParent(&(OpenVRApplication::GetLeftController()->transform));
	
	PointLight* rightlight = new PointLight(glm::vec3(1), 1);
	rightlight->transform.SetParent(&(OpenVRApplication::GetRightController()->transform));


	Engine::Scene()->pointLights.push_back(leftlight);
	Engine::Scene()->pointLights.push_back(rightlight);

	//Engine::Scene()->skybox = new Skybox(skytexture);

	Material* cubemat = new Material(&Shader::StandardShader);
	cubemat->GetProperty<TextureProperty>("u_mainTexture")->texture = nekoTexture;
	cubemat->GetProperty<Float4Property>("u_mainColor")->value = glm::vec4(1);

	Material* whiteMat = new Material(&Shader::BasicShader);
	whiteMat->GetProperty<TextureProperty>("u_mainTexture")->texture = &Texture::White;
	whiteMat->GetProperty<Float4Property>("u_mainColor")->value = glm::vec4(1);

	cube = Engine::Scene()->CreateGameObject("cube", Mesh::Cube(1,1,1,cubemat));
	cube->transform.localPosition.z = -2;

	leftCube = Engine::Scene()->CreateGameObject("leftcube", Mesh::Cube(0.1f, 0.1f, 0.1f, whiteMat));
	leftCube->transform.SetParent(&(OpenVRApplication::GetLeftController()->transform));

	rightCube = Engine::Scene()->CreateGameObject("rightcube", Mesh::Cube(0.1, 0.1, 0.1, whiteMat));
	rightCube->transform.SetParent(&(OpenVRApplication::GetRightController()->transform));


	OVRCamera* camera = new OVRCamera();
	Engine::Scene()->camera = camera;

}

void VRDemo::OnUpdate()
{
	cube->transform.Rotate(Engine::Time().deltaTime, glm::vec3(0, 1, 0));
	//OpenVRApplication::playSpace.Rotate(Engine::Time().deltaTime, glm::vec3(0, 1, 0));


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
