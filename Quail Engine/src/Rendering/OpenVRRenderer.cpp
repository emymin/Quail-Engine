#include "OpenVRRenderer.h"


OpenVRRenderer::OpenVRRenderer() :m_screenShader(&Shader::ScreenShader), m_screenMesh(Mesh::Plane(2.f))
{
	m_screenMesh.material = new Material(m_screenShader);
	m_width = OpenVRApplication::GetWidth();
	m_height = OpenVRApplication::GetHeight();
	m_leftEyeBuffer = new FrameBuffer(m_width, m_height, GL_RGBA, GL_RGBA8);
	m_rightEyeBuffer = new FrameBuffer(m_width, m_height, GL_RGBA, GL_RGBA8);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void OpenVRRenderer::Clear() const
{
	_Clear();
}

void OpenVRRenderer::Draw(const Scene* scene) const
{
	OpenVRApplication::UpdatePoses();

	glm::mat4 headsetPose = OpenVRApplication::GetHeadset()->GetPose();
	headsetPose = OpenVRApplication::playSpace.GetModelMatrix() * headsetPose;
	headsetPose = glm::inverse(headsetPose);

	glm::mat4 leftVP = OpenVRApplication::leftProjectionMatrix*OpenVRApplication::leftHeadtoEyeMatrix;
	glm::mat4 rightVP = OpenVRApplication::rightProjectionMatrix * OpenVRApplication::rightHeadtoEyeMatrix ;

	glm::mat4 skyBoxPose;
	if (scene->skybox) {
		skyBoxPose = OpenVRApplication::GetHeadset()->GetPose();
		skyBoxPose[3][0] = 0;
		skyBoxPose[3][1] = 0;
		skyBoxPose[3][2] = 0;
		glm::mat4 parentPose = OpenVRApplication::playSpace.GetModelMatrix();
		parentPose[3][0] = 0;
		parentPose[3][1] = 0;
		parentPose[3][2] = 0;
		skyBoxPose = parentPose * skyBoxPose;
		skyBoxPose = glm::inverse(skyBoxPose);
	}

	m_leftEyeBuffer->Bind();
	Clear();
	if (scene->skybox) {
	//	_DrawSkybox(scene->skybox, scene->camera->GetPosition(), leftVP*skyBoxPose);
	}
	_DrawScene(scene, leftVP*headsetPose);

	m_rightEyeBuffer->Bind();
	Clear();
	if (scene->skybox) {
	//	_DrawSkybox(scene->skybox, scene->camera->GetPosition(), rightVP*skyBoxPose);
	}
	_DrawScene(scene, rightVP*headsetPose);
	m_rightEyeBuffer->Unbind();
	

	OpenVRApplication::SubmitFrames(m_leftEyeBuffer->GetTexture(),m_rightEyeBuffer->GetTexture());

	DrawToScreen();
}

void OpenVRRenderer::OnResize(unsigned int width, unsigned int height)
{

}

void OpenVRRenderer::DrawToScreen()const
{
	Clear();
	glDisable(GL_DEPTH_TEST);
	m_screenMesh.Bind();
	m_leftEyeBuffer->m_ColorTexture.Bind();
	(m_screenMesh.material->shader)->SetUniform1i("screenTexture", 0);
	glDrawElements(GL_TRIANGLES, m_screenMesh.indexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
	glEnable(GL_DEPTH_TEST);
}
