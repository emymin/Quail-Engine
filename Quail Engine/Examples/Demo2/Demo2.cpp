#include "Demo2.h"

void Demo2::OnInitialize()
{

	Shader* shader = &(Shader::BasicShader);
	ASSERT(shader->Compile());
	shader->Bind();

	Texture* nekoTexture = Texture::Create("./Examples/Assets/Textures/neko.png", false);

	Material* material = new Material(shader);
	material->GetProperty<TextureProperty>("u_mainTexture")->texture = nekoTexture;

	Mesh cube = Mesh::Cube();
	cube.material = material;

	int cubecount = 100;

	for (int i = 0; i < cubecount; i++) {
		GameObject* nekoCube = Engine::Scene()->CreateGameObject("neko"+std::to_string(i), cube);
		nekoCube->transform.localPosition.x = (i - (float)cubecount/2.f)*3;
		nekocubes.push_back(nekoCube);
	}

	PerspectiveCamera* camera = new PerspectiveCamera();
	camera->transform.localPosition.z = -10;
	Engine::Scene()->camera=camera;

	controller = NoClipController(&(camera->transform));

}

void Demo2::OnUpdate()
{
	for (int i = 0; i < nekocubes.size(); i++) {
		GameObject* nekoCube = nekocubes[i];
		nekoCube->transform.SetRotation(glm::vec3(0, Engine::Time().currentTime, 0));
		nekoCube->transform.localPosition.y = sin(i + Engine::Time().currentTime);
	}
	controller.Update();
}

void Demo2::OnGui()
{
	ImGui::Begin("Quail Engine");
	ImGui::Text("Framerate: %1.f Render time: %1.f ms", Engine::Time().fps, Engine::Time().lastRenderTime * 1000);
	ImGui::End();
}

void Demo2::OnClose()
{
}

void Demo2::OnKey(KeyEvent key)
{
}
