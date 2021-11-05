#include "Mesh.h"
#include <filesystem>

#define TINYOBJLOADER_IMPLEMENTATION

#ifdef TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader/tiny_obj_loader.h>
#else
#include <OBJ_Loader.h>
#endif

namespace fs = std::filesystem;


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
	std::vector<Mesh> meshes;
	auto start = std::chrono::steady_clock::now();
	fs::path dir = find_directory_of_path(modelPath);
	Console::Log("Loading model " + modelPath);
#ifdef TINYOBJLOADER_IMPLEMENTATION

	Material* appliedMaterial = material;
	
	tinyobj::ObjReaderConfig reader_config;
	reader_config.triangulate = true;
	tinyobj::ObjReader reader;
	if (!reader.ParseFromFile(modelPath, reader_config)) {
		if (!reader.Error().empty()) {
			Console::Error("TinyObj error: " + reader.Error());
			return meshes;
		}

	}
	auto& attrib = reader.GetAttrib();
	auto& shapes = reader.GetShapes();
	auto& materials = reader.GetMaterials();

	for (size_t s = 0; s < shapes.size();s++) {

		size_t index_offset = 0;
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		
		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			size_t face_vertices = size_t(shapes[s].mesh.num_face_vertices[f]);
			for (size_t v = 0; v < face_vertices; v++) {

				tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
				indices.push_back(index_offset+v);

				float vx = attrib.vertices[3 * size_t(idx.vertex_index) + 0];
				float vy = attrib.vertices[3 * size_t(idx.vertex_index) + 1];
				float vz = attrib.vertices[3 * size_t(idx.vertex_index) + 2];

				float nx, ny, nz;
				if (idx.normal_index >= 0) {
					nx = attrib.normals[3 * size_t(idx.normal_index) + 0];
					ny = attrib.normals[3 * size_t(idx.normal_index) + 1];
					nz = attrib.normals[3 * size_t(idx.normal_index) + 2];
				}
				float tx, ty;
				if (idx.texcoord_index >= 0) {
					tx = attrib.texcoords[2 * size_t(idx.texcoord_index) + 0];
					ty = attrib.texcoords[2 * size_t(idx.texcoord_index) + 1];
				}

				vertices.push_back(vx);
				vertices.push_back(vy);
				vertices.push_back(vz);
				vertices.push_back(tx);
				vertices.push_back(ty);
				vertices.push_back(nx);
				vertices.push_back(ny);
				vertices.push_back(nz);
			}
			index_offset += face_vertices;

		}

		float* vertices_buffer = &vertices[0];
		unsigned int* indices_buffer = &indices[0];

		if (material == nullptr) {
			if (materials.size() > 0) {

				auto matindex = shapes[s].mesh.material_ids[0];
				tinyobj::material_t meshMaterial = materials[matindex];
				std::string diffuseMap = meshMaterial.diffuse_texname;
				Console::Log(diffuseMap);
				if (diffuseMap != "") {
					appliedMaterial = new Material(&Shader::StandardShader);
					fs::path textPath = diffuseMap;
					Texture* texture = Texture::Create((dir / textPath).string(),false);
					appliedMaterial->GetProperty<TextureProperty>("u_mainTexture")->texture = texture;
				}
				else {
					appliedMaterial = nullptr;
				}
			}
			else {
				appliedMaterial = nullptr;
			}
		}


		meshes.push_back(Mesh(vertices_buffer,vertices.size()*sizeof(float), indices_buffer,indices.size(), appliedMaterial));
	}
#else
Material* appliedMaterial = material;

objl::Loader loader;
loader.LoadFile(modelPath);


for (const objl::Mesh& mesh : loader.LoadedMeshes) {
	std::vector<float> vertices;
	vertices.resize(mesh.Vertices.size() * 8);
	std::vector<unsigned int> indices = mesh.Indices;
	for (int i = 0; i < mesh.Vertices.size(); i++) {
		int offset = i * 8;
		objl::Vertex vertex = mesh.Vertices[i];
		vertices[offset + 0] = (vertex.Position.X);
		vertices[offset + 1] = (vertex.Position.Y);
		vertices[offset + 2] = (vertex.Position.Z);
		vertices[offset + 3] = (vertex.TextureCoordinate.X);
		vertices[offset + 4] = (vertex.TextureCoordinate.Y);
		vertices[offset + 5] = (vertex.Normal.X);
		vertices[offset + 6] = (vertex.Normal.Y);
		vertices[offset + 7] = (vertex.Normal.Z);

	}


	float* vertices_buffer = &vertices[0];
	unsigned int* indices_buffer = &indices[0];

	if (material == nullptr) {
		if (mesh.MeshMaterial.map_Kd != "") {
			appliedMaterial = new Material(&Shader::BasicShader);
			fs::path textPath = mesh.MeshMaterial.map_Kd;
			Texture* texture = Texture::Create((dir / textPath).string(),false);
			appliedMaterial->GetProperty<TextureProperty>("u_mainTexture")->texture = texture;
			Console::Log(mesh.MeshMaterial.map_Kd);
		}
		else {
			appliedMaterial = nullptr;
		}
	}
	meshes.push_back(Mesh(vertices_buffer, vertices.size() * sizeof(float), indices_buffer, indices.size(), appliedMaterial));
}
#endif
	auto finish = std::chrono::steady_clock::now();
	double elapsed_seconds = std::chrono::duration_cast<
		std::chrono::duration<double>>(finish - start).count();
	Console::Log(fmt::format("Loaded model {} in {} seconds", modelPath, elapsed_seconds));
	if (meshes.empty()) { Console::Warning("No meshes found in file " + modelPath); }
	return meshes;
}
