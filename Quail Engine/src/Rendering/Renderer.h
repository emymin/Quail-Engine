#pragma once
#include "GLHeaders.h"
#include "Scene.h"


class Renderer {
protected:
	static void _Clear();
	static void _DrawSkybox(Skybox* skybox, glm::vec3 cameraPos, glm::mat4 MVP);
	static void _DrawMesh(const Mesh& mesh, glm::vec3 cameraPos, glm::mat4 MVP, glm::mat4 M,const Scene* scene,glm::vec3 ambientColor);
	static void _DrawScene(const Scene* scene, glm::mat4 VP);
public:
	virtual void Clear() const = 0;
	virtual void Draw(const Scene* scene) const = 0;
	virtual void OnResize(unsigned int width, unsigned int height)=0;
};
