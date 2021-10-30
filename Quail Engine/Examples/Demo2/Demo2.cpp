#include "Demo2.h"

void Demo2::OnInitialize()
{
	std::string vertexShaderSource = ReadTextFromFile("./Examples/Assets/Shaders/basicVertex.glsl");
	std::string fragmentShaderSource = ReadTextFromFile("./Examples/Assets/Shaders/basicFragment.glsl");
	Shader* shader = new Shader(fragmentShaderSource, vertexShaderSource);
	ASSERT(shader->Compile());
	shader->Bind();

	Texture* nekoTexture = new Texture("./Examples/Assets/Textures/neko.png", false);

	Material* material = new Material(shader);
	material->GetProperty<TextureProperty>("u_mainTexture")->texture = nekoTexture;
	material->GetProperty<Float4Property>("u_mainColor")->value = glm::vec4(1, 1, 1, 1);

	Mesh cube = Mesh::LoadOBJ("./Examples/Assets/Models/cube.obj")[0];
	cube.material = material;

	int cubecount = 100;

	for (int i = 0; i < cubecount; i++) {
		GameObject* nekoCube = engine->scene.CreateGameObject("neko"+std::to_string(i), cube);
		nekoCube->transform.localPosition.x = (i - (float)cubecount/2.f)*3;
		nekocubes.push_back(nekoCube);
	}

	PerspectiveCamera* camera = new PerspectiveCamera();
	camera->transform.localPosition.z = 10;
	engine->scene.camera=camera;

}

void Demo2::OnUpdate()
{
	for (int i = 0; i < nekocubes.size(); i++) {
		GameObject* nekoCube = nekocubes[i];
		nekoCube->transform.SetRotation(glm::vec3(0, engine->time.currentTime, 0));
		nekoCube->transform.localPosition.y = sin(i + engine->time.currentTime);
	}
	engine->scene.camera->transform.localPosition.x = sin(engine->time.currentTime*0.1f) * 50;
}

void Demo2::OnGui()
{
	ImGui::Begin("Quail Engine");
	ImGui::Text("Framerate: %1.f Render time: %1.f ms", engine->time.fps, engine->time.deltaTime * 1000);
	ImGui::End();
}

void Demo2::OnClose()
{
}
