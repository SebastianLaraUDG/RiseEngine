#pragma once

#include "CoreTypes.h"

// Forward declaration of concrete types.
// TODO: move this to its own file.
#include "Math/RiseMath.h"
/*
namespace RiseEngine::Math
{
	template<typename T> struct TVector;
}
*/
using Vector3 = RiseEngine::Math::TVector<double>;
using Vector3f = RiseEngine::Math::TVector<float>;

using Matrix4 = RiseEngine::Math::TMatrix<double>;
using Matrix4f = RiseEngine::Math::TMatrix<float>;

// Macros
#if defined(_MSC_VER)
#define FORCEINLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define FORCEINLINE inline __attribute__((always_inline))
#else
#define FORCEINLINE inline
#endif

#define LIKELY likely
#define UNLIKELY unlikely

#define SIZE_IN_BYTES(_x) sizeof(_x) // TODO: keep here or in a specific common rendering file?

// Compliation configuration macros.
#if defined(_DEBUG)
# define CORE_DEBUG 1
#endif

// TODO: implement custom Container types?