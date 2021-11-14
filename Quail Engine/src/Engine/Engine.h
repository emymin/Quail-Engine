#pragma once
#include "GameTime.h"
#include "Input.h"
#include "DesktopRenderer.h"
#include "OpenVRRenderer.h"

class Engine
{
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
	bool m_Focused=true;
	bool m_cursor_capture = false;
public:
	Engine(const std::string& title);
	static void RegisterBehaviour(Behaviour* behaviour) { _instance->behaviours.push_back(behaviour); }
	GameTime time;
	Scene scene;
	GLFWwindow* window;

	static bool Initialize(int window_width=1000,int window_height=1000,RendererType rendererType=RendererType::DesktopRenderer);
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
};

