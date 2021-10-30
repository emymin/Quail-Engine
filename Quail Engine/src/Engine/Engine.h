#pragma once
#include "Scene.h"
#include "Renderer.h"
#include "Game.h"
#include "Key.h"

class Game;

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

	static Scene* Scene() { return &(_instance->scene); }
	static GLFWwindow* Window() { return _instance->window; }
	static GameTime Time() { return _instance->time; }

};

