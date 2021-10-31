#pragma once
#include "Renderer.h"
#include "Game.h"
#include "GameTime.h"

class Engine
{
private:
	static Engine* _instance;
	Renderer m_Renderer;
	Game* m_Game;
	int m_Width, m_Height;
	static void HandleUI();
	static void input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void window_focus_callback(GLFWwindow* window, int focused);
	bool m_Focused=true;
public:
	Engine(Game* game);
	GameTime time;
	Scene scene;
	GLFWwindow* window;

	static bool Initialize(int window_width=1000,int window_height=1000);
	static void Update();
	static void Destroy();

	static void SetResolution(int width, int height);
	static void SetShouldClose();
	static bool ShouldClose();

	static KeyEvent GetKey(Key key);
	static MouseInfo GetMouse();
	static bool IsFocused() { return _instance->m_Focused; }

	static Scene* Scene() { return &(_instance->scene); }
	static GLFWwindow* Window() { return _instance->window; }
	static GameTime Time() { return _instance->time; }
	static Game* GetGame() { return _instance->m_Game; }

	static Engine* GetInstance() { return _instance; }
};

