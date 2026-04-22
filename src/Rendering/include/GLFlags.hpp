#pragma once
#include <RiseEngineCore/Core/CoreTypes.hpp>
#include <vendor/OpenGL/GLEW/include/GL/glew.h>

/*
* Flags to make function documentation easier to understand
* for programmers.
*/

namespace RiseEngine::Rendering
{
	enum ClearFlags : uint32
	{
		Color = GL_COLOR_BUFFER_BIT,
		Depth = GL_DEPTH_BUFFER_BIT
	};
	constexpr ClearFlags operator|(ClearFlags a, ClearFlags b)
	{
		return static_cast<ClearFlags>(
			static_cast<uint32>(a) | static_cast<uint32>(b)
			);
	}

	inline constexpr ClearFlags DefaultClearFlags = ClearFlags::Color | ClearFlags::Depth; // Color and depth buffer.
}