#pragma once
#include "GameTime.h"
#include "Input.h"
#include "DesktopRenderer.h"
#include "OpenVRRenderer.h"
#include "Resources.h"


class Engine
{
public:
	Engine(const std::string& title);
	static void RegisterBehaviour(Behaviour* behaviour) { _instance->behaviours.push_back(behaviour); }
	GameTime time;
	Scene scene;
	GLFWwindow* window;

	template <typename T=DesktopRenderer>
	static bool Initialize(int width = 1000, int height = 1000,bool vsync=true) {
		Console::Log("Initializing Quail Engine...");

		_instance->m_Width = width;
		_instance->m_Height = height;

		InitGL(vsync);
		InitIMGUI();
		Resources::Initialize();
		_instance->m_Renderer = new T();

		Console::Log("Finished initializing Quail Engine, initializing game...");

		for (auto behaviour : _instance->behaviours) {
			behaviour->OnInitialize();
		}

		return true;
	}


	static void Update();
	static void Destroy();

	static void SetResolution(int width, int height);
	static void SetShouldClose();
	static bool ShouldClose();
	static void SetCursorCapture(bool value);
	static bool GetCursorCapture();

	static unsigned int GetWidth();
	static unsigned int GetHeight();

	static KeyEvent GetKey(Key key);
	static MouseInfo GetMouse();
	static bool IsFocused() { return _instance->m_Focused; }

	static Scene* Scene() { return &(_instance->scene); }
	static GLFWwindow* Window() { return _instance->window; }
	static const GameTime Time() { return _instance->time; }
	static Behaviour* GetBehaviour(std::string name);
	static Renderer* GetRenderer() { return _instance->m_Renderer; }

	static Engine* GetInstance() { return _instance; }

private:

	static Engine* _instance;
	Renderer* m_Renderer;
	std::vector<Behaviour*> behaviours;
	int m_Width, m_Height;
	std::string m_Title;

	static void HandleUI();
	static void input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void window_focus_callback(GLFWwindow* window, int focused);

	static bool InitGL(bool vsync=true);
	static bool InitIMGUI();

	bool m_Focused=true;
	bool m_cursor_capture = false;
};

