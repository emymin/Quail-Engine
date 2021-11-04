#include "ExampleGame.h"

void ExampleGame::OnInitialize()
{

	Shader* unlit = &(Shader::BasicShader);
	Shader* standard = &(Shader::StandardShader);

	Texture* testTexture = Texture::Create("./Examples/Assets/Textures/test.png");
	Texture* nekoTexture = Texture::Create("./Examples/Assets/Textures/neko.png", false);
	Texture* skytexture = Texture::Create("./Examples/Assets/Textures/skybox.hdr");

	Engine::Scene()->skybox = new Skybox(skytexture);

	Material* material2 = new Material(standard);
	material2->GetProperty<TextureProperty>("u_mainTexture")->texture = nekoTexture;

	Material* material = new Material(standard);
	material->GetProperty<TextureProperty>("u_mainTexture")->texture = testTexture;



	GameObject* testbun = Engine::Scene()->CreateGameObject("bun", Mesh::LoadOBJ("./Examples/Assets/Models/bunny.obj"));
	GameObject* nekoCube = Engine::Scene()->CreateGameObject("neko", Mesh::Cube());
	GameObject* sponza = Engine::Scene()->CreateGameObject("sponza", Mesh::LoadOBJ("./Examples/Assets/Models/sponza/sponza.obj"));


	testbun->meshes[0].material = material;
	nekoCube->meshes[0].material = material2;

	testbun->transform.localPosition.x = -1;
	nekoCube->transform.localPosition.x = 1;

	nekoCube->transform.localScale *= 0.5f;
	testbun->transform.localScale *= 1.f;

	PerspectiveCamera* camera = new PerspectiveCamera();
	camera->transform.localPosition.z = 3;
	Engine::Scene()->camera = camera;

	controller = NoClipController(&(camera->transform));
}

void ExampleGame::OnUpdate()
{
	controller.Update();

	GameObject* testbun = Engine::Scene()->Get("bun");
	GameObject* nekoCube = Engine::Scene()->Get("neko");

	testbun->transform.SetRotation(0, Engine::Time().currentTime, 0);
	nekoCube->transform.SetRotation(sin(Engine::Time().currentTime), cos(Engine::Time().currentTime), cos(Engine::Time().currentTime));

	testbun->meshes[0].material->GetProperty<Float4Property>("u_mainColor")->value = glm::vec4(abs(sin(Engine::Time().currentTime)), abs(cos(Engine::Time().currentTime)), 1, 1);
}

void ExampleGame::OnGui()
{

	ImGui::Begin("Quail Engine");
	ImGui::Text("Framerate: %1.f Render time: %.3f ms", Engine::Time().fps, Engine::Time().lastRenderTime * 1000);
	ImGui::End();
}

void ExampleGame::OnClose()
{
}

void ExampleGame::OnKey(KeyEvent key)
{
	if (key.action == KeyAction::PRESS) {
		switch (key.key) {
		case Key::Esc: {Engine::SetShouldClose(); break; }
		default: {break; }
		}
	}
}
