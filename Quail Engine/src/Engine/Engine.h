#pragma once
#include "Scene.h"
#include "Renderer.h"
#include "Game.h"

class Game;

class Engine
{
private:
	static Engine* instance;
	Renderer m_Renderer;
	Game* m_Game;
	int m_Width, m_Height;
	static void HandleInput();
	static void HandleUI();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
public:
	Engine(Game* game);
	GameTime time;
	Scene scene;
	GLFWwindow* window;
	static bool Initialize(int window_width=1000,int window_height=1000);
	static void SetResolution(int width, int height);
	static bool ShouldClose();
	static void Update();
	static void Destroy();

	static Scene* Scene() { return &(instance->scene); }
	static GLFWwindow* Window() { return instance->window; }
	static GameTime Time() { return instance->time; }


};

