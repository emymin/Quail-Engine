#pragma once
#include "GLHeaders.h"
#include "Scene.h"

#include "FrameBuffer.h"


class Renderer {
private:
	FrameBuffer m_buffer;
	Shader* m_screenShader;
	Mesh m_screenMesh;
	void DrawSkybox(const Scene* scene) const;
	void DrawScene(const Scene* scene) const;
public:
	Renderer(unsigned int width,unsigned int height);;
	void Clear() const;
	void Draw(const Scene* scene) const;
};