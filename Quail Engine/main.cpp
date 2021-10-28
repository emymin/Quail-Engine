#include "Renderer.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Material.h"
#include "Texture.h"
#if _DEBUG
#include "Debug.h"
#endif
#include "Utils.h"

int vwidth = 1000;
int vheight= 1000;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	vwidth = width;
	vheight = height;
}



int main() {

#pragma region Initialization

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	std::cout << "Quail Engine is running..." << std::endl;


	GLFWwindow* window = glfwCreateWindow(1000, 1000, "Quail Engine", NULL, NULL);
	if (window == NULL) {
		std::cout << "Error Creating Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
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
	glViewport(0, 0, vwidth, vheight);
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
#pragma endregion



#pragma region VertexObject


	float vertices[] = {
		//positions        //uv
		-1.0f,1.0f,0.0f, 0.0f,0.0f,
		1.0f,1.0f,0.0f,  1.0f,0.0f,
		-1.0f,-1.0f,0.0f, 0.0f,1.0f,
		1.0f,-1.0f,0.0f, 1.0f,1.0f
	};
	unsigned int indices[] = {
		0,1,2,
		1,3,2
	};


	VertexArray va;
	VertexBuffer vb(vertices, sizeof(vertices));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	IndexBuffer ib(indices, 6);

#pragma endregion


	std::string vertexShaderSource = ReadTextFromFile("./Shaders/basicVertex.glsl");
	std::string fragmentShaderSource = ReadTextFromFile("./Shaders/basicFragment.glsl");
	Shader shader(fragmentShaderSource, vertexShaderSource);
	ASSERT(shader.Compile());
	shader.Bind();

	Texture texture("./Textures/test.png");
	Texture texture2("./Textures/neko.png");
	
	glm::vec4 color(1, 0, 1, 1);
	glm::vec4 color2(0, 1, 0, 1);

	Material material(shader);
	material.GetProperty<Float4Property>("u_mainColor")->value = color;
	material.GetProperty<TextureProperty>("u_mainTexture")->texture = &texture;

	Material material2(shader);
	material2.GetProperty<TextureProperty>("u_mainTexture")->texture = &texture2;
	material2.GetProperty<Float4Property>("u_mainColor")->value = color2;

	Renderer renderer;


	float lastTime = 0;
	while (!glfwWindowShouldClose(window)) {
		float time = glfwGetTime();
		float deltaTime = time - lastTime;
		lastTime = time;

		float fps = 1 / deltaTime;


#pragma region KeyHandling
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
#pragma endregion

		renderer.Clear();
		
		glm::mat4 proj = glm::perspective(90.f, 1.f, 0.1f, 500.f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		model = glm::rotate(model, time, glm::vec3(0, 1, 0));

		glm::mat4 mvp = proj * view * model;
		shader.SetUniformMat4f("u_MVP", mvp);

		material.ApplyUniforms();

		renderer.Draw(va, ib, shader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(1, 0, 0));
		mvp = proj * view * model;
		shader.SetUniformMat4f("u_MVP", mvp);
		material2.ApplyUniforms();

		renderer.Draw(va, ib, shader);




		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Quail Engine");
		ImGui::Text("Framerate: %1.f Render time: %1.f ms",fps,deltaTime*1000);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());




		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}