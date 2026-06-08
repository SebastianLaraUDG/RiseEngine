#pragma once
#include "ITexture.hpp"
#include <array>
#include <string>

namespace RiseEngine::Rendering
{
	/*
   * Used for skyboxes, environment maps, reflections, etc.
   */
	class ITextureCubemap : public ITexture
	{
	public:
		virtual ~ITextureCubemap() = default;

		// 6 paths. Order: +X, -X, +Y, -Y, +Z, -Z.
		virtual void LoadFromFiles(const std::array<std::string, 6>& filepaths) = 0;
		ETextureDimension GetDimension() const override { return ETextureDimension::TextureCubemap; }
	};
}