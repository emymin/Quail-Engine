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

	GameObject* testbun = engine->scene.CreateGameObject("bun", Mesh::LoadOBJ("./Examples/Assets/Models/bunny.obj"));
	GameObject* nekoCube = engine->scene.CreateGameObject("neko", Mesh::LoadOBJ("./Examples/Assets/Models/cube.obj"));

	testbun->meshes[0].material = material;
	nekoCube->meshes[0].material = material2;

	testbun->transform.localPosition.x = -1;
	nekoCube->transform.localPosition.x = 1;

	nekoCube->transform.localScale *= 0.5f;
	testbun->transform.localScale *= 1.f;

	PerspectiveCamera* camera = new PerspectiveCamera();
	camera->transform.localPosition.z = 3;
	engine->scene.camera = camera;
}

void ExampleGame::OnUpdate()
{
	GameObject* testbun = engine->scene.Get("bun");
	GameObject* nekoCube = engine->scene.Get("neko");

	testbun->transform.SetRotation(0, engine->time.currentTime, 0);
	nekoCube->transform.SetRotation(sin(engine->time.currentTime), cos(engine->time.currentTime), cos(engine->time.currentTime));

	testbun->meshes[0].material->GetProperty<Float4Property>("u_mainColor")->value = glm::vec4(abs(sin(engine->time.currentTime)), abs(cos(engine->time.currentTime)), 1, 1);
}

void ExampleGame::OnGui()
{

	ImGui::Begin("Quail Engine");
	ImGui::Text("Framerate: %1.f Render time: %1.f ms", engine->time.fps, engine->time.deltaTime * 1000);
	ImGui::End();
}

void ExampleGame::OnClose()
{
}
