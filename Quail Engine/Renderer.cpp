#include "Renderer.h"

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Renderer::Draw(const SceneObject object)
{
	glm::mat4 MVP = m_viewProjection * object.transform.GetModelMatrix();
	for (const Mesh& mesh : object.meshes) {
		if (mesh.material != nullptr) {
			mesh.Bind();
			mesh.material->shader->SetUniformMat4f("u_MVP", MVP);
			glDrawElements(GL_TRIANGLES, mesh.indexBuffer.GetCount(), GL_UNSIGNED_INT, 0);
		}
	}
}

