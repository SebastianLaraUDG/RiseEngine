#pragma once
#include <RiseEngineCore/Core/CoreTypes.hpp>

// Rendering Hardware Interface File.
// Defines common rendering types without
// coupling in a specific API.

namespace RiseEngine::Rendering
{
	enum class EClearFlags : uint32
	{
		Color = 1 << 0,
		Depth = 1 << 1,
		Stencil = 1 << 2,
	};
	inline EClearFlags operator|(EClearFlags a, EClearFlags b)
	{
		return static_cast<EClearFlags>(
			static_cast<uint32>(a) | static_cast<uint32>(b)
			);
	}
	inline bool HasFlag(EClearFlags flags, EClearFlags flag)
	{
		return (static_cast<uint32>(flags) & static_cast<uint32>(flag)) != 0;
	}

	enum class EPolygonMode : uint8
	{
		Fill,
		Wireframe,
	};

	enum class EPrimitiveType : uint8
	{
		Triangles,
		Lines,
		Points,
	};
	
	enum class EVertexDataType : uint8
	{
		Float,
		Int,
		UnsignedInt,
		Byte,
		UnsignedByte,
	};

	enum class EBufferFrequency: uint8
	{
		Static,
		Dynamic,
		Stream,
	};

	enum class EBufferAccess : uint8
	{
		Draw,
		Read,
		Copy,
	};
}