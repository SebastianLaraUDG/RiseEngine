#include "OpenGLTexture2D.hpp"
#include <glad/glad.h>
#include <vendor/stb/stb_image.h>

using OpenGLTexture2D = RiseEngine::Rendering::OpenGLTexture2D;

OpenGLTexture2D::OpenGLTexture2D(const TextureSpec& spec) : spec_(spec)
{
	spec_.dimension = ETextureDimension::Texture2D; // Force this.
	Allocate();
}

OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
{
	spec_.dimension = ETextureDimension::Texture2D; // Force this.
	LoadFromFile(path);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &id_);
}

void OpenGLTexture2D::Bind(uint32 slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, id_);
}

void OpenGLTexture2D::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLTexture2D::SetData(const void* data, uint32 size)
{
	glBindTexture(GL_TEXTURE_2D, id_);
	glTexSubImage2D(
		GL_TEXTURE_2D,
		0,
		0,
		0,
		spec_.width,
		spec_.height,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data
	);
	Unbind();
}

void OpenGLTexture2D::LoadFromFile(const std::string& filepath)
{
	int32 width, height, channels;
	stbi_set_flip_vertically_on_load(1);

	uint8* data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

	spec_.width = static_cast<uint32>(width);
	spec_.height = static_cast<uint32>(height);
	spec_.format = (channels == 4) ? ETextureFormat::RGBA8 : ETextureFormat::RGB8;

	// If a texture was already allocated, delete it before creating a new one.
	if (id_)
	{
		glDeleteTextures(1, &id_);
	}

	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_);

	uint32 internalFormat = TranslateFormat(spec_.format);
	uint32 dataFormat = (channels == 4) ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data/*cast?*/);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TranslateFilter(spec_.filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TranslateFilter(spec_.filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TranslateWrap(spec_.wrap));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TranslateWrap(spec_.wrap));
	
	Unbind();
	stbi_image_free(data);
}

void OpenGLTexture2D::Allocate()
{
	glGenTextures(1, &id_);
	glBindTexture(GL_TEXTURE_2D, id_);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		TranslateFormat(spec_.format),
		spec_.width,
		spec_.height,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TranslateFilter(spec_.filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TranslateFilter(spec_.filter));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TranslateWrap(spec_.wrap));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TranslateWrap(spec_.wrap));

	Unbind();
}

uint32 OpenGLTexture2D::TranslateFormat(ETextureFormat format)
{
	switch (format)
	{
	case ETextureFormat::RGB8:					return GL_RGB8;
	case ETextureFormat::RGBA8:					return GL_RGBA8;
	case ETextureFormat::Depth24Stencil8:		return GL_DEPTH24_STENCIL8;
	default:									return GL_RGBA8;
	}
}

uint32 OpenGLTexture2D::TranslateFilter(ETextureFilter filter)
{
	switch (filter)
	{
	case ETextureFilter::Linear:		return GL_LINEAR;
	case ETextureFilter::Nearest:		return GL_NEAREST;
	default:							return GL_LINEAR;
	}
}

uint32 OpenGLTexture2D::TranslateWrap(ETextureWrap wrap)
{
	switch (wrap)
	{
	case ETextureWrap::Repeat:						return GL_REPEAT;
	case ETextureWrap::ClampToEdge:					return GL_CLAMP_TO_EDGE;
	case ETextureWrap::MirroredRepeat:				return GL_MIRRORED_REPEAT;
	default:										return GL_REPEAT;
	}
}