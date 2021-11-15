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
	vr::TrackedDevicePose_t poses[vr::k_unMaxTrackedDeviceCount];
	vr::VRCompositor()->WaitGetPoses(poses, vr::k_unMaxTrackedDeviceCount, NULL, 0);
	
	glm::mat4 headsetPose = OpenVRApplication::toGLM(poses[vr::k_unTrackedDeviceIndex_Hmd].mDeviceToAbsoluteTracking);
	headsetPose = glm::inverse(headsetPose);

	glm::mat4 leftP = OpenVRApplication::GetProjectionMatrix(vr::Hmd_Eye::Eye_Left);
	glm::mat4 leftHTE = OpenVRApplication::GetHeadToEyeMatrix(vr::Hmd_Eye::Eye_Left);

	glm::mat4 rightP = OpenVRApplication::GetProjectionMatrix(vr::Hmd_Eye::Eye_Right);
	glm::mat4 rightHTE = OpenVRApplication::GetHeadToEyeMatrix(vr::Hmd_Eye::Eye_Right);


	glm::mat4 leftVP = leftP*leftHTE*headsetPose;
	glm::mat4 rightVP = rightP*rightHTE*headsetPose;

	m_leftEyeBuffer->Bind();
	Clear();
	_DrawSkybox(scene->skybox, scene->camera->GetPosition(), leftVP);
	_DrawScene(scene, leftVP);

	m_rightEyeBuffer->Bind();
	Clear();
	_DrawSkybox(scene->skybox, scene->camera->GetPosition(), rightVP);
	_DrawScene(scene, rightVP);
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
