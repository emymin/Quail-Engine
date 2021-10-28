#include "Renderer.h"

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::Draw(const Mesh& mesh) const
{
	if (mesh.material != nullptr) {
		mesh.Bind();
		glDrawElements(GL_TRIANGLES, mesh.indexBuffer->GetCount(), GL_UNSIGNED_INT, 0);
	}
}

