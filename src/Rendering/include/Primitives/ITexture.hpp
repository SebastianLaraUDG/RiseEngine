#pragma once

namespace RiseEngine::Rendering
{
	enum class ETextureFormat : uint8
	{
		None = 0,
		RGB8,
		RGBA8,
		Depth24Stencil8
	};

	enum class ETextureFilter : uint8
	{
		Linear,
		Nearest
	};

	enum class ETextureWrap : uint8
	{
		Repeat,
		ClampToEdge,
		MirroredRepeat
	};

	enum class ETextureDimension : uint8
	{
		Texture2D,
		Texture3D,
		TextureCubemap,
		Texture2DArray,
		CubemapArray
	};

	struct TextureSpec
	{
		uint32 width = 1;
		uint32 height = 1;
		ETextureFormat format = ETextureFormat::RGBA8;
		ETextureFilter filter = ETextureFilter::Linear;
		ETextureWrap wrap = ETextureWrap::Repeat;
		ETextureDimension dimension; // = ETextureDimension::Texture2D;
	};

	/*
	* Base interface for all textures.
	* Platform agnostic.
	*/
	class ITexture
	{
	public:
		virtual ~ITexture() = default;

		virtual void Bind(uint32 slot = 0) const = 0;
		virtual void Unbind() const = 0;
		
		virtual uint32 GetWidth() const = 0;
		virtual uint32 GetHeight() const = 0;
		virtual ETextureFormat GetFormat() const = 0;
		virtual ETextureDimension GetDimension() const = 0;
		virtual const TextureSpec& GetSpec() const = 0;
		virtual uint32 GetId() const = 0;
	};
}