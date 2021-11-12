#pragma once
#include "GLHeaders.h"
#include "RenderBuffer.h"
#include "Texture.h"
class FrameBuffer
{
private:
	unsigned int m_RendererID;
	RenderBuffer m_DepthStencilBuffer;
	Texture m_ColorTexture;
public:
	FrameBuffer(unsigned int width,unsigned int height);
	void Bind() const;
	void Unbind() const;
	void Destroy();
	void Resize(unsigned int width, unsigned int height);

	friend class DesktopRenderer;
};

