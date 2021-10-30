#include "Engine.h"
#include "GLHeaders.h"
#if _DEBUG
#include "Debug.h"
#endif

Engine* Engine::instance;

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Engine::SetResolution(width, height);
}

Engine::Engine(Game* game)
{
	if (instance != nullptr) { return; }
	instance = this;
	m_Game = game;

}

bool Engine::Initialize(int width,int height)
{
	instance->m_Width = width;
	instance->m_Height = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::cout << "Quail Engine is running..." << std::endl;
	std::cout << "Game: " << instance->m_Game->name << std::endl;


	instance->window = glfwCreateWindow(width, height, instance->m_Game->name.c_str(), NULL, NULL);
	if (instance->window == NULL) {
		std::cout << "Error Creating Window" << std::endl;
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(instance->window);
	glfwSwapInterval(1);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return false;
	}
	glfwSetFramebufferSizeCallback(instance->window, framebuffer_size_callback);
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
	glViewport(0, 0, instance->m_Width, instance->m_Height);
	glClearColor(0.f, 0.f, 0.f, 1.0f);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(instance->window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	instance->m_Game->OnInitialize();

	return true;

}

void Engine::SetResolution(int width, int height)
{
	std::cout << "Setting resolution "<<width<<" "<<height<< std::endl;
	glViewport(0, 0, width, height);
	instance->scene.camera->SetAspectRatio(width, height);
	instance->m_Width = width;
	instance->m_Height = height;
}

bool Engine::ShouldClose()
{
	return glfwWindowShouldClose(instance->window);
}

void Engine::Update()
{
	instance->time.currentTime = GameTime::GetTime();
	instance->time.deltaTime = instance->time.currentTime - instance->time.lastTime;
	instance->time.lastTime = instance->time.currentTime;
	instance->time.fps = 1 / instance->time.deltaTime;

	HandleInput();
	
	instance->m_Game->OnUpdate();
	
	instance->m_Renderer.Clear();
	instance->m_Renderer.Draw(&instance->scene);

	HandleUI();

	glfwSwapBuffers(instance->window);
	glfwPollEvents();

}



void Engine::HandleInput()
{
	if (glfwGetKey(instance->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(instance->window, true);
	}
}

void Engine::HandleUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	instance->m_Game->OnGui();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void Engine::Destroy()
{
	instance->m_Game->OnClose();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(instance->window);
	glfwTerminate();
}
