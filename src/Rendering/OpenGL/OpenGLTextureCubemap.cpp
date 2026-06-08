#include "OpenGLTextureCubemap.hpp"

using OpenGLTextureCubemap = RiseEngine::Rendering::OpenGLTextureCubemap;

OpenGLTextureCubemap::OpenGLTextureCubemap(const TextureSpec& spec) : spec_(spec)
{
	spec_.dimension = ETextureDimension::TextureCubemap; // Force this.

	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id_);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, TranslateFilter(spec_.filter));
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, TranslateFilter(spec_.filter));
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	Unbind();
}

OpenGLTextureCubemap::~OpenGLTextureCubemap()
{
	glDeleteTextures(1, &id_);
}

void OpenGLTextureCubemap::Bind(uint32 slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id_);
}

void OpenGLTextureCubemap::Unbind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void OpenGLTextureCubemap::LoadFromFiles(const std::array<std::string, 6>& filepaths)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, id_);

	int32 width, height, channels;
	stbi_set_flip_vertically_on_load(0); // Cubemap textures should not be flipped.

	for (uint32 index = 0; index < 6; ++index)
	{
		uint8* data = stbi_load(filepaths[index].c_str(), &width, &height, &channels, 0);

		uint32 dataFormat = (channels == 4) ? GL_RGBA : GL_RGB;
		uint32 internalFormat = TranslateFormat((channels == 4) ? ETextureFormat::RGBA8 : ETextureFormat::RGB8);

		// Remember: 6 paths. Order: +X, -X, +Y, -Y, +Z, -Z.
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data /* cast?*/);

		stbi_image_free(data);
	}

	spec_.width = static_cast<uint32>(width);
	spec_.height = static_cast<uint32>(height);

	Unbind();
}

uint32 OpenGLTextureCubemap::TranslateFormat(ETextureFormat format)
{
	switch (format)
	{
	case ETextureFormat::RGB8:					return GL_RGB8;
	case ETextureFormat::RGBA8:					return GL_RGBA8;
	default:									return GL_RGBA8;
	}
}

uint32 OpenGLTextureCubemap::TranslateFilter(ETextureFilter filter)
{
	switch (filter)
	{
	case ETextureFilter::Linear:		return GL_LINEAR;
	case ETextureFilter::Nearest:		return GL_NEAREST;
	default:							return GL_LINEAR;
	}
}
