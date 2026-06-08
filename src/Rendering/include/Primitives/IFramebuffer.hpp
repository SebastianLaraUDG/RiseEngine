#pragma once

namespace RiseEngine::Rendering
{
	class ITexture2D;

	struct FramebufferSpec
	{
		uint32 width = 800;
		uint32 height = 600;
	};

	/*
	* A frame buffer is basically a texture cotainer where we can render to instead of rendering directly to the screen. This is useful for post-processing effects, ImGUI, shadow mapping, and more.
	* 
	* It has three main components:
	* Color attachment: the texture that stores the color of every pixel.
	* Depth attachment: where the depth of every pixel is stored.
	* Stencil attachment: for masking effects. (not used for now, I'm just trying to implement ImGUI)
	*/
	class IFramebuffer
	{
	public:
		virtual ~IFramebuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual  void Resize(const uint32 width, const uint32 height) = 0;

		virtual ITexture2D* GetColorAttachment() const = 0;
		virtual const FramebufferSpec& GetSpec() const = 0;
	};
}