#include "Texture.h"
#include <stb_image/stb_image.h>
#include "Console.h"

std::unordered_map<std::string, Texture> Texture::_cache;

Texture::Texture(const std::string& path,bool clamp) : m_RendererID(0),m_FilePath(path),m_LocalBuffer(nullptr),m_Width(0),m_Height(0),m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	Console::Log("Loading texture " + path);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (clamp) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);

	glGenerateMipmap(GL_TEXTURE_2D);

	if (m_LocalBuffer) {
		stbi_image_free(m_LocalBuffer);
	}

	Unbind();
}

Texture::Texture(unsigned char* buffer,int width,int height):m_LocalBuffer(buffer),m_Width(width),m_Height(height),m_FilePath("INTERNAL"),m_BPP(0),m_RendererID(0)
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	Unbind();
}

Texture* Texture::Create(const std::string& path, bool clamp /*= true*/)
{
	if (_cache.find(path) == _cache.end()) {
		_cache[path] = Texture(path, clamp);
		return &(_cache[path]);
	}
	else {
		return &(_cache[path]);
	}
}

/*Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}*/

void Texture::Bind(unsigned int slot /*= 0*/) const
{
	glActiveTexture(GL_TEXTURE0+slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture Texture::White;
