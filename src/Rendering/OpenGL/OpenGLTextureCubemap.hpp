#pragma once
#include <Rendering/include/Primitives/ITextureCubemap.hpp>

namespace RiseEngine::Rendering
{
    class OpenGLTextureCubemap : public ITextureCubemap
    {
    public:
		explicit OpenGLTextureCubemap(const TextureSpec& spec);
        ~OpenGLTextureCubemap() override;

		void Bind(uint32 slot = 0) const override;
        void Unbind() const override;

        void LoadFromFiles(const std::array<std::string, 6>& filepaths) override;

    public:
        inline uint32 GetWidth() const { return spec_.width; };
        inline uint32 GetHeight() const { return spec_.height; };
        inline ETextureFormat GetFormat() const { return spec_.format; };
        inline ETextureDimension GetDimension() const { return spec_.dimension; }
        inline const TextureSpec& GetSpec() const { return spec_; }
        inline uint32 GetId() const { return id_; };
    private:
		static uint32 TranslateFormat(ETextureFormat format);
		static uint32 TranslateFilter(ETextureFilter filter);

    private:
		uint32 id_ = 0;
		TextureSpec spec_;
    };
}