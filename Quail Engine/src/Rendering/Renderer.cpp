#include "Renderer.h"

void Renderer::_Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::_DrawSkybox(Skybox* skybox, glm::vec3 cameraPos, glm::mat4 MVP)
{
	glDepthMask(GL_FALSE);
	skybox->m_Mesh.Bind();
	skybox->m_Mesh.material->shader->SetUniformMat4f("u_MVP", MVP);
	skybox->m_Mesh.material->shader->SetUniform3f("u_cameraPos", cameraPos.x, cameraPos.y, cameraPos.z);
	glDrawElements(GL_TRIANGLES, skybox->m_Mesh.indexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
	glDepthMask(GL_TRUE);
}

void Renderer::_DrawMesh(const Mesh& mesh, glm::vec3 cameraPos, glm::mat4 MVP, glm::mat4 M,const Scene* scene,glm::vec3 ambientColor)
{
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

void Renderer::_DrawScene(const Scene* scene, glm::mat4 VP)
{
	glm::vec3 ambientColor = glm::vec3(0);
	if (scene->skybox != nullptr) {
		ambientColor = scene->skybox->ambientColor;
	}

	for (auto pair : scene->m_gameObjects) {

		GameObject* object = &(pair.second);

		glm::mat4 M = object->transform.GetModelMatrix();
		glm::mat4 MVP = VP * M;
		glm::vec3 cameraPos = scene->camera->transform.localPosition;

		for (const Mesh& mesh : object->meshes) {
			_DrawMesh(mesh, cameraPos, MVP, M, scene, ambientColor);
		}
	}
}
