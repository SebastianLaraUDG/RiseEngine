#pragma once
#include <Rendering/include/Primitives/ITexture2D.hpp>
namespace RiseEngine::Rendering
{
	class OpenGLTexture2D : public ITexture2D
	{
	public:
		explicit OpenGLTexture2D(const TextureSpec& spec);
		explicit OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D() override;

		void Bind(uint32 slot = 0) const override;
		void Unbind() const override;

		void SetData(const void* data, uint32 size) override;
		void LoadFromFile(const std::string& filepath) override;

	public:
		inline uint32 GetId() const override { return id_; }
		inline uint32 GetWidth() const override { return spec_.width; }
		inline uint32 GetHeight() const override { return spec_.height; }
		inline ETextureFormat GetFormat() const override { return spec_.format; }
		inline const TextureSpec& GetSpec() const override { return spec_; }
		inline ETextureDimension GetDimension() const override { return ETextureDimension::Texture2D; }

	private:
		void Allocate();

		static uint32 TranslateFormat(ETextureFormat format);
		static uint32 TranslateFilter(ETextureFilter filter);
		static uint32 TranslateWrap(ETextureWrap wrap);

	private:
		uint32 id_ = 0;
		TextureSpec spec_;
	};
}