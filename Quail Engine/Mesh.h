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
	void Bind() const;
	static Mesh Plane(float size = 1.f,Material* material=nullptr);
};

