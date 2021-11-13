#pragma once
#include "Renderer.h"
#include "FrameBuffer.h"

class DesktopRenderer :public Renderer {
private:
	FrameBuffer m_buffer;
	Shader* m_screenShader;
	Mesh m_screenMesh;
	void DrawSkybox(const Scene* scene) const;
	void DrawScene(const Scene* scene) const;
public:
	DesktopRenderer(unsigned int width, unsigned int height);
	void Clear() const override;
	void Draw(const Scene* scene) const override;
};