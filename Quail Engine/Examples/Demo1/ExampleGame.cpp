#include "ExampleGame.h"

void ExampleGame::OnInitialize()
{

	std::string vertexShaderSource = ReadTextFromFile("./Examples/Assets/Shaders/basicVertex.glsl");
	std::string fragmentShaderSource = ReadTextFromFile("./Examples/Assets/Shaders/basicFragment.glsl");
	Shader* shader = new Shader(fragmentShaderSource, vertexShaderSource);
	ASSERT(shader->Compile());
	shader->Bind();

	Texture* testTexture = new Texture("./Examples/Assets/Textures/test.png");
	Texture* nekoTexture = new Texture("./Examples/Assets/Textures/neko.png", false);

	glm::vec4 color2(1, 1, 1, 1);

	Material* material = new Material(shader);
	material->GetProperty<TextureProperty>("u_mainTexture")->texture = testTexture;

	Material* material2 = new Material(shader);
	material2->GetProperty<TextureProperty>("u_mainTexture")->texture = nekoTexture;
	material2->GetProperty<Float4Property>("u_mainColor")->value = color2;

	GameObject* testbun = Engine::Scene()->CreateGameObject("bun", Mesh::LoadOBJ("./Examples/Assets/Models/bunny.obj"));
	GameObject* nekoCube = Engine::Scene()->CreateGameObject("neko", Mesh::LoadOBJ("./Examples/Assets/Models/cube.obj"));

	testbun->meshes[0].material = material;
	nekoCube->meshes[0].material = material2;

	testbun->transform.localPosition.x = -1;
	nekoCube->transform.localPosition.x = 1;

	nekoCube->transform.localScale *= 0.5f;
	testbun->transform.localScale *= 1.f;

	PerspectiveCamera* camera = new PerspectiveCamera();
	camera->transform.localPosition.z = -3;
	Engine::Scene()->camera = camera;

	controller = NoClipController(&(camera->transform), 2.f);
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
	if (key.key == Esc && key.action == PRESS) {
		Engine::SetShouldClose();
	}
}
