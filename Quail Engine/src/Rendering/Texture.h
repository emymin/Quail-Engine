#pragma once

#include "GLHeaders.h"
#include <iostream>

class Texture
{
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	Texture() {}
public:
	Texture(unsigned char* buffer,int width,int height);
	Texture(const std::string& path,bool clamp=true);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

	static Texture White;
};

