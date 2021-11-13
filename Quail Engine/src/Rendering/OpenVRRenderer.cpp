#include "OpenVRRenderer.h"


OpenVRRenderer::OpenVRRenderer()
{

}

void OpenVRRenderer::Initialize()
{
	m_width = application->m_width;
	m_height = application->m_height;
	m_leftEyeBuffer = new FrameBuffer(m_width, m_height);
	m_rightEyeBuffer = new FrameBuffer(m_width, m_height);
}

void OpenVRRenderer::Clear() const
{
	_Clear();
}

void OpenVRRenderer::Draw(const Scene* scene) const
{
	m_leftEyeBuffer->Bind();
	glClearColor(1, 0, 0, 1);
	Clear();
	m_rightEyeBuffer->Bind();
	glClearColor(0, 1, 0, 1);
	Clear();
	m_rightEyeBuffer->Unbind();
	application->SubmitFrames(m_leftEyeBuffer->GetTexture(),m_rightEyeBuffer->GetTexture());
}
