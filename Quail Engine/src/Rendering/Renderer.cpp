#include "Renderer.h"
#include "Console.h"

void Renderer::DrawSkybox(const Scene* scene) const
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

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Renderer::Draw(const Scene* scene) const
{
	if (scene->camera == nullptr) {
		Console::Warning("Scene has no camera");
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
				mesh.material->shader->SetUniform3f("u_cameraPos", cameraPos.x, cameraPos.y, cameraPos.z);

				if (scene->skybox != nullptr) {
					mesh.material->shader->SetUniform3f("u_ambientColor", ambientColor.r,ambientColor.g,ambientColor.b);
					mesh.material->shader->SetUniform1f("u_ambientStrength",scene->skybox->ambientStrength);
				}
				
				glDrawElements(GL_TRIANGLES, mesh.indexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
			}
		}
	}
}

