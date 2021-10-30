#pragma once
#include "Scene.h"
#include "Renderer.h"
#include "Game.h"

class Game;

class Engine
{
private:
	Renderer m_Renderer;
	Game* m_Game;
	int m_Width, m_Height;
public:
	GameTime time;
	Scene scene;
	GLFWwindow* window;
	bool Initialize(Game* game,int width=1000,int height=1000);
	void SetResolution(int width, int height) {
		m_Width = width;
		m_Height = height;
		glViewport(0, 0, width, height);
	}
	bool ShouldClose() {
		return glfwWindowShouldClose(window);
	}
	void Update();
	void Destroy();


};

