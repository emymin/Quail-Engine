#include "Mesh.h"
#include <OBJ_Loader.h>

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

std::vector<Mesh> Mesh::LoadOBJ(std::string modelPath,Material* material)
{
	std::vector<Mesh> meshes;
	
	objl::Loader loader;
	loader.LoadFile(modelPath);

	for (const objl::Mesh& mesh : loader.LoadedMeshes) {
		std::vector<float> vertices;
		vertices.resize(mesh.Vertices.size() * 5);
		std::vector<unsigned int> indices = mesh.Indices;
		for (int i=0;i<mesh.Vertices.size();i++){
			int offset = i * 5;
			objl::Vertex vertex = mesh.Vertices[i];
			vertices[offset+0] = (vertex.Position.X);
			vertices[offset + 1] = (vertex.Position.Y);
			vertices[offset + 2] = (vertex.Position.Z);
			vertices[offset + 3] = (vertex.TextureCoordinate.X);
			vertices[offset + 4] = (vertex.TextureCoordinate.Y);
		}

		float* vertices_buffer = &vertices[0];
		unsigned int* indices_buffer = &indices[0];

		VertexArray va;
		VertexBuffer vb(vertices_buffer, vertices.size() * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
		IndexBuffer ib(indices_buffer, indices.size());

		meshes.push_back(Mesh(va, ib, material));
	}
	return meshes;
}
