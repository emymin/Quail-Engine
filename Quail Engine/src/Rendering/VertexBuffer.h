#pragma once
class VertexBuffer
{
private:
	unsigned int m_RendererID;
	float* m_LocalBuffer;
	unsigned int m_size;
public:
	VertexBuffer(const void* data, unsigned int size);
//	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
};

