#include "OpenGLFramebuffer.hpp"
#include <glad/glad.h>
// #include <Rendering/include/GLErrorLibrary.hpp>

using OpenGLFramebuffer = RiseEngine::Rendering::OpenGLFramebuffer;

OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpec& spec) : spec_(spec)
{
	Invalidate();
}

OpenGLFramebuffer::~OpenGLFramebuffer()
{
	glDeleteFramebuffers(1, &id_);
	glDeleteRenderbuffers(1, &depthAttachment_);
}

void OpenGLFramebuffer::Bind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, id_);
	glViewport(0, 0, spec_.width, spec_.height);
}

void OpenGLFramebuffer::Unbind() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void OpenGLFramebuffer::Resize(const uint32 width, const uint32 height)
{
	spec_.width = width;
	spec_.height = height;
	Invalidate();
}

void OpenGLFramebuffer::Invalidate()
{
	if (id_)
	{
		glDeleteFramebuffers(1, &id_);
		glDeleteRenderbuffers(1, &depthAttachment_);
		colorAttachment_.reset();
	}

	glGenFramebuffers(1, &id_);
	glBindFramebuffer(GL_FRAMEBUFFER, id_);

	// Color attachment.
	TextureSpec colorSpec;
	colorSpec.width = spec_.width;
	colorSpec.height = spec_.height;
	colorSpec.format = ETextureFormat::RGBA8;
	colorSpec.filter = ETextureFilter::Linear;
	colorSpec.wrap = ETextureWrap::ClampToEdge;

	colorAttachment_ = std::make_unique<OpenGLTexture2D>(colorSpec);
	glFramebufferTexture2D(
		GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D,
		colorAttachment_->GetId(),
		0);

	// Depth attachment - renderbuffer. More efficient than a texture for depth.
	glGenRenderbuffers(1, &depthAttachment_);
	glBindRenderbuffer(GL_RENDERBUFFER, depthAttachment_);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, spec_.width, spec_.height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthAttachment_);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
