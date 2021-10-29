#include "Engine.h"
#include "GLHeaders.h"
#if _DEBUG
#include "Debug.h"
#endif

bool Engine::Initialize(int width,int height)
{
	m_Width = width;
	m_Height = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::cout << "Quail Engine is running..." << std::endl;


	window = glfwCreateWindow(1000, 1000, "Quail Engine", NULL, NULL);
	if (window == NULL) {
		std::cout << "Error Creating Window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
#if _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	int flags; glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
	if (GL_CONTEXT_FLAG_DEBUG_BIT) {
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(glDebugOutput, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}
#endif
	glViewport(0, 0, m_Width, m_Height);
	glClearColor(0.f, 0.f, 0.f, 1.0f);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

#pragma region TemporaryUserCode
	std::string vertexShaderSource = ReadTextFromFile("./Assets/Shaders/basicVertex.glsl");
	std::string fragmentShaderSource = ReadTextFromFile("./Assets/Shaders/basicFragment.glsl");
	Shader* shader = new Shader(fragmentShaderSource, vertexShaderSource);
	ASSERT(shader->Compile());
	shader->Bind();

	Texture* testTexture = new Texture("./Assets/Textures/test.png");
	Texture* nekoTexture = new Texture("./Assets/Textures/neko.png", false);

	glm::vec4 color2(1, 1, 1, 1);

	Material* material = new Material(shader);
	material->GetProperty<TextureProperty>("u_mainTexture")->texture = testTexture;

	Material* material2 = new Material(shader);
	material2->GetProperty<TextureProperty>("u_mainTexture")->texture = nekoTexture;
	material2->GetProperty<Float4Property>("u_mainColor")->value = color2;

	GameObject* testbun = m_Scene.CreateGameObject("bun", Mesh::LoadOBJ("./Assets/Models/bunny.obj"));
	GameObject* nekoCube = m_Scene.CreateGameObject("neko", Mesh::LoadOBJ("./Assets/Models/cube.obj"));

	testbun->meshes[0].material = material;
	nekoCube->meshes[0].material = material2;

	testbun->transform.localPosition.x = -1;
	nekoCube->transform.localPosition.x = 1;

	nekoCube->transform.localScale *= 0.5f;
	testbun->transform.localScale *= 1.f;

	PerspectiveCamera* camera=new PerspectiveCamera();
	camera->transform.localPosition.z = 3;
	m_Scene.camera = camera;

#pragma endregion

	return true;

}

void Engine::Update()
{
	float time = glfwGetTime();
	float deltaTime = time - lastTime;
	lastTime = time;

	float fps = 1 / deltaTime;

#pragma region TemporaryUserCode
	GameObject* testbun = m_Scene.Get("bun");
	GameObject* nekoCube = m_Scene.Get("neko");

	testbun->transform.SetRotation(0, time, 0);
	nekoCube->transform.SetRotation(sin(time), cos(time), cos(time));

	testbun->meshes[0].material->GetProperty<Float4Property>("u_mainColor")->value = glm::vec4(abs(sin(time)), abs(cos(time)), 1, 1);
#pragma endregion


	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	m_Scene.camera->SetAspectRatio(m_Width,m_Height);
	
	m_Renderer.Clear();
	m_Renderer.Draw(&m_Scene);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Quail Engine");
	ImGui::Text("Framerate: %1.f Render time: %1.f ms", fps, deltaTime * 1000);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
	glfwPollEvents();

}

void Engine::Destroy()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}
