#include "Renderer.h"

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Renderer::Draw(const GameObject* object,Camera* camera)
{
	glm::mat4 MVP = camera->GetViewProjectionMatrix() * object->transform.GetModelMatrix();
	for (const Mesh& mesh : object->meshes) {
		if (mesh.material != nullptr) {
			mesh.Bind();
			mesh.material->shader->SetUniformMat4f("u_MVP", MVP);
			glDrawElements(GL_TRIANGLES, mesh.indexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
		}
	}
}

void Renderer::Draw(const Scene* scene)
{
	if (scene->camera == nullptr) {
		std::cout << "Scene has no camera!" << std::endl;
		return;
	}
	for (auto pair : scene->gameObjects) {
		Draw(pair.second, scene->camera);
	}
}

