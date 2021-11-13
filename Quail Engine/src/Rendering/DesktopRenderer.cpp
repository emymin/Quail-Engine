#include "DesktopRenderer.h"
DesktopRenderer::DesktopRenderer(unsigned int width, unsigned int height) :m_buffer(width, height), m_screenShader(&Shader::ScreenShader), m_screenMesh(Mesh::Plane(2.f))
{
	Material* screenMaterial = new Material(m_screenShader);
	m_screenMesh.material = screenMaterial;
}
void DesktopRenderer::DrawSkybox(const Scene* scene) const
{
	glDepthMask(GL_FALSE);
	scene->skybox->m_Mesh.Bind();
	glm::vec3 cameraPos = scene->camera->transform.localPosition;
	glm::mat4 v = glm::mat4(glm::mat3(scene->camera->GetViewMatrix()));
	glm::mat4 MVP = scene->camera->GetProjectionMatrix() * v;
	glm::mat4 m;
	scene->skybox->m_Mesh.material->shader->SetUniformMat4f("u_MVP", MVP);
	scene->skybox->m_Mesh.material->shader->SetUniform3f("u_cameraPos", cameraPos.x, cameraPos.y, cameraPos.z);
	glDrawElements(GL_TRIANGLES, scene->skybox->m_Mesh.indexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
	glDepthMask(GL_TRUE);
}

void DesktopRenderer::DrawScene(const Scene* scene) const
{
	if (scene->camera == nullptr) {
		//Console::Warning("Scene has no camera");
		return;
	}

	glm::vec3 ambientColor = glm::vec3(0);
	if (scene->skybox != nullptr) {
		DrawSkybox(scene);
		ambientColor = scene->skybox->ambientColor;
	}

	glm::mat4 VP = scene->camera->GetViewProjectionMatrix();

	for (auto pair : scene->m_gameObjects) {

		GameObject* object = &(pair.second);

		glm::mat4 M = object->transform.GetModelMatrix();
		glm::mat4 MVP = VP * M;
		glm::vec3 cameraPos = scene->camera->transform.localPosition;

		for (const Mesh& mesh : object->meshes) {
			if (mesh.material != nullptr) {
				mesh.Bind();

				mesh.material->shader->SetUniformMat4f("u_MVP", MVP);
				mesh.material->shader->SetUniformMat4f("u_M", M);
				mesh.material->shader->SetUniform3f("rend.u_cameraPos", cameraPos.x, cameraPos.y, cameraPos.z);
				for (int i = 0; i < 10; i++) {
					std::string uniformName = fmt::format("rend.pointLights[{}]", i);
					if (i < scene->pointLights.size()) {
						PointLight* light = scene->pointLights[i];
						light->Apply(mesh.material->shader, uniformName);
					}
					else {
						PointLight::empty.Apply(mesh.material->shader, uniformName);
					}
				}

				if (scene->skybox != nullptr) {
					mesh.material->shader->SetUniform3f("rend.u_ambientColor", ambientColor.r, ambientColor.g, ambientColor.b);
					mesh.material->shader->SetUniform1f("rend.u_ambientStrength", scene->skybox->ambientStrength);
					scene->skybox->texture->Bind(1);
					mesh.material->shader->SetUniform1i("rend.u_environmentMap", 1);
				}

				glDrawElements(GL_TRIANGLES, mesh.indexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
			}
		}
	}
}


void DesktopRenderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

