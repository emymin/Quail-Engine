#include "Mesh.h"

void Mesh::Bind() const
{
	vertexArray.Bind();
	indexBuffer.Bind();
	material->shader->Bind();
	material->ApplyUniforms();
}

Mesh Mesh::Plane(float size,Material* material)
{
	float front = 0.5f * size;
	float back = -0.5f * size;
	float vertices[] = {
		//positions        //uv
		back,front,0.0f, 0.0f,0.0f,
		front,front,0.0f,  1.0f,0.0f,
		back,back,0.0f, 0.0f,1.0f,
		front,back,0.0f, 1.0f,1.0f
	};
	unsigned int indices[] = {
		0,1,2,
		1,3,2
	};

	VertexArray va;
	VertexBuffer vb(vertices, sizeof(vertices));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);
	IndexBuffer ib(indices, 6);

	return Mesh(va, ib, material);
}
