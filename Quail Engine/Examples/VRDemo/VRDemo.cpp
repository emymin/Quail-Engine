#include "VRDemo.h"
#include "OVRCamera.h"

void VRDemo::OnInitialize()
{
	Texture* nekoTexture = Texture::Create("./Examples/Assets/Textures/neko.png", false);
	Texture* skytexture = Texture::Create("./Examples/Assets/Textures/skybox.hdr", true, false);

	PointLight* light = new PointLight(glm::vec3(1), 10, glm::vec3(1, 1, 1));
	Engine::Scene()->pointLights.push_back(light);

	Engine::Scene()->skybox = new Skybox(skytexture);

	Material* cubemat = new Material(&Shader::StandardShader);
	cubemat->GetProperty<TextureProperty>("u_mainTexture")->texture = nekoTexture;
	cubemat->GetProperty<Float4Property>("u_mainColor")->value = glm::vec4(1);

	cube = Engine::Scene()->CreateGameObject("cube", Mesh::Cube(1,1,1,cubemat));
	cube->transform.localPosition.z = -2;

	leftCube = Engine::Scene()->CreateGameObject("leftcube", Mesh::Cube(0.1f, 0.1f, 0.1f,cubemat));
	rightCube = Engine::Scene()->CreateGameObject("rightcube", Mesh::Cube(0.1, 0.1, 0.1, cubemat));

	OVRCamera* camera = new OVRCamera();
	Engine::Scene()->camera = camera;

}

void VRDemo::OnUpdate()
{
	cube->transform.Rotate(Engine::Time().deltaTime, glm::vec3(0, 1, 0));
	leftCube->transform.localPosition = OpenVRApplication::GetDevice(1)->GetPosition();
	rightCube->transform.localPosition = OpenVRApplication::GetDevice(2)->GetPosition();

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
