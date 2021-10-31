#include "Engine.h"
#include "Console.h"

#if _DEBUG
#include "Debug.h"
#endif

Engine* Engine::_instance;

void Engine::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	Engine::SetResolution(width, height);
}

void Engine::window_focus_callback(GLFWwindow* window, int focused)
{
	_instance->m_Focused = (focused != 0);
}

Engine::Engine(Game* game)
{
	Console::Log(game->name);
	if (_instance != nullptr) { return; }
	_instance = this;
	m_Game = game;
}

bool Engine::Initialize(int width,int height)
{

	Console::Log("Initializing Quail Engine...");
	
	_instance->m_Width = width;
	_instance->m_Height = height;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_instance->window = glfwCreateWindow(width, height, _instance->m_Game->name.c_str(), NULL, NULL);
	if (_instance->window == NULL) {
		Console::Error("Error creating window!");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(_instance->window);
	glfwSwapInterval(1);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Console::Error("Failed to initialize GLAD");
		return false;
	}

	//SET CALLBACKS
	glfwSetFramebufferSizeCallback(_instance->window, framebuffer_size_callback);
	glfwSetKeyCallback(_instance->window, input_callback);
	glfwSetWindowFocusCallback(_instance->window, window_focus_callback);

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
	glViewport(0, 0, _instance->m_Width, _instance->m_Height);
	glClearColor(0.f, 0.f, 0.f, 1.0f);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(_instance->window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	Console::Log("Initialized engine, initializing game...");

	_instance->m_Game->OnInitialize();

	return true;

}

void Engine::SetResolution(int width, int height)
{
	Console::Log(fmt::format("Setting resolution to {} {}", width, height));
	glViewport(0, 0, width, height);
	_instance->scene.camera->SetAspectRatio(width, height);
	_instance->m_Width = width;
	_instance->m_Height = height;
}

void Engine::SetShouldClose()
{
	glfwSetWindowShouldClose(_instance->window, true);
}

bool Engine::ShouldClose()
{
	return glfwWindowShouldClose(_instance->window);
}

KeyEvent Engine::GetKey(Key key)
{
	int state = glfwGetKey(_instance->window,key);
	return KeyEvent(key, state);
}

MouseInfo Engine::GetMouse()
{
	double xpos, ypos;
	glfwGetCursorPos(_instance->window, &xpos, &ypos);
	return MouseInfo(xpos, ypos);

}

void Engine::Update()
{
	_instance->time.currentTime = GameTime::GetTime();
	_instance->time.deltaTime = _instance->time.currentTime - _instance->time.lastTime;
	_instance->time.lastTime = _instance->time.currentTime;
	_instance->time.fps = 1 / _instance->time.deltaTime;
	
	_instance->m_Game->OnUpdate();
	
	_instance->m_Renderer.Clear();
	_instance->m_Renderer.Draw(&_instance->scene);

	HandleUI();

	_instance->time.lastRenderTime = GameTime::GetTime() - _instance->time.currentTime;

	glfwSwapBuffers(_instance->window);
	glfwPollEvents();


}



void Engine::input_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	_instance->m_Game->OnKey(KeyEvent(key,action));
}

void Engine::HandleUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	_instance->m_Game->OnGui();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}


void Engine::Destroy()
{
	Console::Log("Shutdown...");
	_instance->m_Game->OnClose();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(_instance->window);
	glfwTerminate();
}
