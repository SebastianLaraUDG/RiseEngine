#pragma once
#include <Rendering/include/Primitives/IFramebuffer.hpp>
#include <memory>
#include "OpenGLTexture2D.hpp"

namespace RiseEngine::Rendering
{
	class ITexture2D;

	// TODO: This class uses openGl textures. I should wrap textures in a
	// Texture class (API agnostic) and then an opengl texture class that inherits from it.

	class OpenGLFramebuffer : public IFramebuffer
	{
	public:
		explicit OpenGLFramebuffer(const FramebufferSpec& spec);
		~OpenGLFramebuffer() override;

		void Bind() const override;
		void Unbind() const override;
		void Resize(const uint32 width, const uint32 height) override;
		
	public:
		inline ITexture2D* GetColorAttachment() const override { return colorAttachment_.get(); }
		inline const FramebufferSpec& GetSpec() const override { return spec_; }
	private:
		void Invalidate(); // Create or recreate the framebuffer and its attachments.
	private:
		uint32 id_ = 0;
		uint32 depthAttachment_ = 0; // for now.
		std::unique_ptr<OpenGLTexture2D> colorAttachment_;
		FramebufferSpec spec_;
	};
}