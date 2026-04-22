#pragma once
#include <cstdint>

// Signed types.
namespace RiseEngineTypes
{
	namespace CoreTypes
	{
		using int8 = int8_t;
		using int16 = int16_t;
		using int32 = int32_t;
		using int64 = int64_t;

		// Unsigned types.
		using uint8 = uint8_t;
		using uint16 = uint16_t;
		using uint32 = uint32_t;
		using uint64 = uint64_t;

		// Floating point types.
		using f32 = float;
		using f64 = double;
	}
}

// Signed types.
using int8 = RiseEngineTypes::CoreTypes::int8;
using int16 = RiseEngineTypes::CoreTypes::int16;
using int32 = RiseEngineTypes::CoreTypes::int32;
using int64 = RiseEngineTypes::CoreTypes::int64;

// Unsigned types.
using uint8 = RiseEngineTypes::CoreTypes::uint8;
using uint16 = RiseEngineTypes::CoreTypes::uint16;
using uint32 = RiseEngineTypes::CoreTypes::uint32;
using uint64 = RiseEngineTypes::CoreTypes::uint64;

// Floating point types.
using f32 = RiseEngineTypes::CoreTypes::f32;
using f64 = RiseEngineTypes::CoreTypes::f64;