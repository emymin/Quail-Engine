#pragma once

#include "GLHeaders.h"
#include <iostream>
#include <unordered_map>

class Texture
{
private:
	static std::unordered_map<std::string, Texture> _cache;
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture() {}
	Texture(unsigned char* buffer,int width,int height, unsigned int internalformat = GL_RGBA8, unsigned int format = GL_RGBA, unsigned int type = GL_UNSIGNED_BYTE);
	Texture(const std::string& path,bool clamp=true,bool mipmap=true);

	static Texture* Create(const std::string& path, bool clamp = true,bool mipmap=true);

	void Bind(unsigned int slot = 0) const;
	void Unbind(unsigned int slot = 0)const;
	void Destroy();

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

	glm::vec4 GetAverageColor();

	static Texture White;

	friend class Resources;
	friend class FrameBuffer;
};

