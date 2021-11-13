#include "DesktopRenderer.h"
DesktopRenderer::DesktopRenderer(unsigned int width, unsigned int height) :m_buffer(width, height), m_screenShader(&Shader::ScreenShader), m_screenMesh(Mesh::Plane(2.f))
{
	Material* screenMaterial = new Material(m_screenShader);
	m_screenMesh.material = screenMaterial;
}
void DesktopRenderer::DrawSkybox(const Scene* scene) const
{

	glm::vec3 cameraPos = scene->camera->transform.localPosition;
	glm::mat4 v = glm::mat4(glm::mat3(scene->camera->GetViewMatrix()));
	glm::mat4 MVP = scene->camera->GetProjectionMatrix() * v;
	_DrawSkybox(scene->skybox, cameraPos, MVP);
}

void DesktopRenderer::DrawScene(const Scene* scene) const
{
	if (scene->camera == nullptr) {
		//Console::Warning("Scene has no camera");
		return;
	}
	if (scene->skybox != nullptr) {
		DrawSkybox(scene);
	}
	glm::mat4 VP = scene->camera->GetViewProjectionMatrix();
	_DrawScene(scene, VP);
}


void DesktopRenderer::Clear() const
{
	_Clear();
}


void DesktopRenderer::Draw(const Scene* scene) const
{
	m_buffer.Bind();
	Clear();
	DrawScene(scene);
	m_buffer.Unbind();

	Clear();
	glDisable(GL_DEPTH_TEST);
	m_screenMesh.Bind();
	m_buffer.m_ColorTexture.Bind();
	(m_screenMesh.material->shader)->SetUniform1i("screenTexture", 0);
	glDrawElements(GL_TRIANGLES, m_screenMesh.indexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
	glEnable(GL_DEPTH_TEST);

}

