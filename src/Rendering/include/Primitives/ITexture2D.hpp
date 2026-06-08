#pragma once
#include "ITexture.hpp"
#include <string>

namespace RiseEngine::Rendering
{
	/*
	* Used for sprites, framebuffer color attachments, UI, etc.
	*/
	class ITexture2D : public ITexture
	{
	public:
		virtual ~ITexture2D() = default;

		// Upload raw pixel data to the GPU.
		virtual void SetData(const void* data, uint32 size) = 0;
		virtual void LoadFromFile(const std::string& filepath) = 0;
		
		ETextureDimension GetDimension() const override { return ETextureDimension::Texture2D; }
	};
}