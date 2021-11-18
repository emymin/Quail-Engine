#include "VRDemo.h"
#include "OVRCamera.h"

void VRDemo::OnInitialize()
{
	Texture* nekoTexture = Texture::Create("./Examples/Assets/Textures/neko.png", false);
	Texture* skytexture = Texture::Create("./Examples/Assets/Textures/skybox.hdr", true, false);

	//PointLight* light = new PointLight(glm::vec3(1), 1);
	//Engine::Scene()->pointLights.push_back(light);

	Engine::Scene()->skybox = new Skybox(skytexture);

	Material* cubemat = new Material(&Shader::StandardShader);
	cubemat->GetProperty<TextureProperty>("u_mainTexture")->texture = nekoTexture;
	cubemat->GetProperty<Float4Property>("u_mainColor")->value = glm::vec4(1);

	Material* whiteMat = new Material(&Shader::BasicShader);
	whiteMat->GetProperty<TextureProperty>("u_mainTexture")->texture = &Texture::White;
	whiteMat->GetProperty<Float4Property>("u_mainColor")->value = glm::vec4(1);

	cube = Engine::Scene()->CreateGameObject("cube", Mesh::Cube(1,1,1,cubemat));
	cube->transform.localPosition.z = -2;

	Mesh nekoGunMesh = Mesh::LoadOBJ("./Examples/Assets/Models/nekogun.obj", cubemat)[0];

	leftGun = Engine::Scene()->CreateGameObject("leftcube", nekoGunMesh);
	leftGun->transform.SetParent(&(OpenVRApplication::GetLeftController()->transform));

	rightGun = Engine::Scene()->CreateGameObject("rightcube", nekoGunMesh);
	rightGun->transform.SetParent(&(OpenVRApplication::GetRightController()->transform));


	OVRCamera* camera = new OVRCamera();
	Engine::Scene()->camera = camera;

}

void VRDemo::OnUpdate()
{
	cube->transform.Rotate(Engine::Time().deltaTime, glm::vec3(0, 1, 0));

	if (OpenVRApplication::GetLeftController()->isButtonPressed(vr::k_EButton_Grip)) {
		Console::Log("Pressed");
	}
	


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
