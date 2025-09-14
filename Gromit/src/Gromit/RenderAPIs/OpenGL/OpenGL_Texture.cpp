#include "OpenGL_Texture.h"
#include <glad/glad.h>

namespace Gromit::OpenGL
{
	OpenGL_Texture::OpenGL_Texture(const TextureAsset& asset)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &TextureId);
		glBindTexture(GL_TEXTURE_2D, TextureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//todo format convert
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, asset.m_width, asset.m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, asset.m_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	OpenGL_Texture::~OpenGL_Texture()
	{
		glDeleteTextures(1, &TextureId);
	}

	void OpenGL_Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, TextureId);
	}

	void OpenGL_Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, NULL);
	}
}