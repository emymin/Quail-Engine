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
	FrameBuffer(){}
public:
	FrameBuffer(unsigned int width,unsigned int height);
	void Bind() const;
	void Unbind() const;
	void Destroy();
	void Resize(unsigned int width, unsigned int height);
	Texture* GetTexture() { return &m_ColorTexture; }
	friend class DesktopRenderer;
	friend class OpenVRRenderer;
};

