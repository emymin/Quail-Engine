#include "Mesh.h"
#include <OBJ_Loader.h>

Mesh::Mesh(float* vertices, int vertices_size, unsigned int* indices, int indices_count,Material* material) : material(material),indexBuffer(indices,indices_count)
{
	vertexArray = VertexArray();
	VertexBuffer vb(vertices, vertices_size);
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);
	layout.Push<float>(3);
	vertexArray.AddBuffer(vb, layout);

}

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
		//positions        //uv           //normal
		back,front,0.0f, 0.0f,0.0f,    0.f,0.f,1.f,
		front,front,0.0f,  1.0f,0.0f,  0.f,0.f,1.f,
		back,back,0.0f, 0.0f,1.0f,     0.f,0.f,1.f,
		front,back,0.0f, 1.0f,1.0f,     0.f,0.f,1.f,
	};
	unsigned int indices[] = {
		0,1,2,
		1,3,2
	};

	return Mesh(vertices, sizeof(vertices), indices, 6, material);
}



Mesh Mesh::Cube(float width, float height, float depth, Material* material /*= nullptr*/)
{
	float front = 0.5f * depth;
	float side = 0.5f * width;
	float top = 0.5f * height;

	float vertices[] = {
		-side,-top,front,0,0,-1,0,0,
		-side,top,front,0,1,-1,0,0,
		-side,top,-front,-1,1,-1,0,0,
		-side,-top,-front,-1,0,-1,0,0,
		-side,-top,-front,-1,2,0,0,-1,
		-side,top,-front,-1,1,0,0,-1,
		side,top,-front,0,1,0,0,-1,
		side,-top,-front,0,2,0,0,-1,
		side,-top,-front,1,1,1,0,0,
		side,top,-front,0,1,1,0,0,
		side,top,front,0,0,1,0,0,
		side,-top,front,1,0,1,0,0,
		side,-top,front,2,0,0,0,1,
		side,top,front,1,0,0,0,1,
		-side,top,front,1,-1,0,0,1,
		-side,-top,front,2,-1,0,0,1,
		-side,-top,-front,-1,-1,0,-1,0,
		side,-top,-front,0,-1,0,-1,0,
		side,-top,front,0,0,0,-1,0,
		-side,-top,front,-1,0,0,-1,0,
		side,top,-front,1,0,0,1,0,
		-side,top,-front,0,0,0,1,0,
		-side,top,front,0,-1,0,1,0,
		side,top,front,1,-1,0,1,0
	};
	unsigned int indices[] = {
		0,1,3,1,2,3,4,5,7,5,6,7,8,9,11,9,10,11,12,13,15,13,14,15,16,17,19,17,18,19,20,21,23,21,22,23
	};

	return Mesh(vertices, sizeof(vertices), indices, sizeof(indices) / sizeof(unsigned int));

}

std::vector<Mesh> Mesh::LoadOBJ(std::string modelPath,Material* material)
{
	Console::Log("Loading model " + modelPath);
	std::vector<Mesh> meshes;
	
	objl::Loader loader;
	loader.LoadFile(modelPath);

	for (const objl::Mesh& mesh : loader.LoadedMeshes) {
		std::vector<float> vertices;
		vertices.resize(mesh.Vertices.size() * 8);
		std::vector<unsigned int> indices = mesh.Indices;
		for (int i=0;i<mesh.Vertices.size();i++){
			int offset = i * 8;
			objl::Vertex vertex = mesh.Vertices[i];
			vertices[offset+0] = (vertex.Position.X);
			vertices[offset + 1] = (vertex.Position.Y);
			vertices[offset + 2] = (vertex.Position.Z);
			vertices[offset + 3] = (vertex.TextureCoordinate.X);
			vertices[offset + 4] = (vertex.TextureCoordinate.Y);
			vertices[offset + 5] = (vertex.Normal.X);
			vertices[offset + 6] = (vertex.Normal.Y);
			vertices[offset + 7] = (vertex.Normal.Z);

		}

		/*Console::Log(modelPath + " vertices");
		for (const float& vertex : vertices) {
			std::cout << vertex << ",";
		}
		std::cout << std::endl;
		Console::Log(modelPath + " indices");
		for (const float& index : indices) {
			std::cout << index << ",";
		}
		std::cout << std::endl;
		*/

		float* vertices_buffer = &vertices[0];
		unsigned int* indices_buffer = &indices[0];


		meshes.push_back(Mesh(vertices_buffer,vertices.size()*sizeof(float), indices_buffer,indices.size(), material));
	}
	if (meshes.empty()) { Console::Warning("No meshes found in file " + modelPath); }
	else {
		Console::Log("Loaded model " + modelPath);
	}

	return meshes;
}
