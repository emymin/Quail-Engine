#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Material.h"



class Mesh
{
public:
	VertexArray vertexArray;
	IndexBuffer indexBuffer;
	Material* material;
	Mesh(VertexArray& va, IndexBuffer& ib, Material* material = nullptr) : vertexArray(va), indexBuffer(ib), material(material) {}
	Mesh(float* vertices,int vertices_size,unsigned int* indices,int indices_count,Material* material=nullptr);
	void Bind() const;
	static Mesh Plane(float size = 1.f,Material* material=nullptr);
	static Mesh Cube(float width=1.f, float height=1.f, float depth=1.f, Material* material = nullptr);
	static std::vector<Mesh> LoadOBJ(std::string modelPath,Material* material=nullptr);
};

