#pragma once
#include "Scene.h"
#include "Renderer.h"

class Engine
{
private:
	Scene m_Scene;
	Renderer m_Renderer;
	int m_Width; int m_Height;
	float fps;
	float deltaTime;
	float lastTime;
public:
	GLFWwindow* window;
	bool Initialize(int width=1000,int height=1000);
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

