#include "OpenVRRenderer.h"


void OpenVRRenderer::Initialize()
{
	m_width = application->m_width;
	m_height = application->m_height;
	m_leftEyeBuffer = new FrameBuffer(m_width, m_height,GL_RGBA,GL_RGBA8);
	m_rightEyeBuffer = new FrameBuffer(m_width, m_height,GL_RGBA,GL_RGBA8);
}

void OpenVRRenderer::Clear() const
{
	_Clear();
}

void OpenVRRenderer::Draw(const Scene* scene) const
{
	OVRCamera* camera = (OVRCamera*)scene->camera;
	if (camera->transform.GetParent() != &(application->m_devices[0].transform)) {
		camera->transform.SetParent(&(application->m_devices[0].transform));
	}
	if (camera != nullptr) {
		glm::mat4 leftVP = camera->GetLeftProjectionMatrix() * camera->GetLeftViewMatrix();
		glm::mat4 rightVP = camera->GetRightProjectionMatrix() * camera->GetRightViewMatrix();

		m_leftEyeBuffer->Bind();
		Clear();
		_DrawSkybox(scene->skybox, camera->transform.localPosition, leftVP);
		//_DrawScene(scene, leftVP);

		m_rightEyeBuffer->Bind();
		Clear();
		_DrawSkybox(scene->skybox, camera->transform.localPosition, rightVP);
		//_DrawScene(scene, rightVP);
		m_rightEyeBuffer->Unbind();
	}

	application->SubmitFrames(m_leftEyeBuffer->GetTexture(),m_rightEyeBuffer->GetTexture());

	Clear();
	glDisable(GL_DEPTH_TEST);
	m_screenMesh.Bind();
	m_leftEyeBuffer->m_ColorTexture.Bind();
	(m_screenMesh.material->shader)->SetUniform1i("screenTexture", 0);
	glDrawElements(GL_TRIANGLES, m_screenMesh.indexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
	glEnable(GL_DEPTH_TEST);
	
}
