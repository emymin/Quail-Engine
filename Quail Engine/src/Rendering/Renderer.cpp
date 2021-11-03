#include "Renderer.h"
#include "Console.h"

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Renderer::Draw(const GameObject* object,Camera* camera)
{
	glm::mat4 M = object->transform.GetModelMatrix();
	glm::mat4 MVP = camera->GetViewProjectionMatrix() * M;
	glm::vec3 cameraPos = camera->transform.localPosition;
	for (const Mesh& mesh : object->meshes) {
		if (mesh.material != nullptr) {
			mesh.Bind();
			mesh.material->shader->SetUniformMat4f("u_MVP", MVP);
			mesh.material->shader->SetUniformMat4f("u_M", M);
			mesh.material->shader->SetUniform3f("u_cameraPos",cameraPos.x, cameraPos.y, cameraPos.z);
			glDrawElements(GL_TRIANGLES, mesh.indexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
		}
	}
}

void Renderer::Draw(const Scene* scene)
{
	if (scene->camera == nullptr) {
		Console::Warning("Scene has no camera");
		return;
	}
	if (scene->skybox != nullptr) {
		scene->skybox->m_Mesh.Bind();
		glm::vec3 cameraPos = scene->camera->transform.localPosition;
		glm::mat4 v = glm::mat4(glm::mat3(scene->camera->GetViewMatrix()));
		glm::mat4 MVP = scene->camera->GetProjectionMatrix() * v;
		glm::mat4 m;
		scene->skybox->m_Mesh.material->shader->SetUniformMat4f("u_MVP", MVP);
		scene->skybox->m_Mesh.material->shader->SetUniform3f("u_cameraPos", cameraPos.x, cameraPos.y, cameraPos.z);
	}

	for (auto pair : scene->m_gameObjects) {
		Draw(&(pair.second), scene->camera);
	}
}

