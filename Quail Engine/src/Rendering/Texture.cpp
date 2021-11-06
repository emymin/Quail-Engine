#include "Texture.h"
#include <stb_image/stb_image.h>
#include "Console.h"

std::unordered_map<std::string, Texture> Texture::_cache;

Texture::Texture(const std::string& path,bool clamp,bool mipmap) : m_RendererID(0),m_FilePath(path),m_LocalBuffer(nullptr),m_Width(0),m_Height(0),m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	Console::Log("Loading texture " + path);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
	if (clamp) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (mipmap) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	if (m_LocalBuffer) {
		//stbi_image_free(m_LocalBuffer);
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

Texture* Texture::Create(const std::string& path, bool clamp,bool mipmap /*= true*/)
{
	if (_cache.find(path) == _cache.end()) {
		_cache[path] = Texture(path, clamp,mipmap);
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

void Texture::Unbind(unsigned int slot)const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, 0);
}

glm::vec4 Texture::GetAverageColor()
{
	glm::vec4 averageColor = glm::vec4(0);
	int width = GetWidth();
	int height = GetHeight();
	int stridex = (4*width)/8;
	int stridey = (4*height)/8;
	int n = 0;
	for (int x = 0; x < width*4; x += stridex) {
		for (int y = 0; y < height*4; y += stridey) {
			float r = m_LocalBuffer[x + y * width];
			float g = m_LocalBuffer[1+x + y * width];
			float b = m_LocalBuffer[2+x + y * width];
			float a = m_LocalBuffer[3+x + y * width];
			averageColor += glm::vec4(r, g, b, a);
			n++;
		}
	}
	averageColor = normalize(averageColor);
	return averageColor;
}

Texture Texture::White;
