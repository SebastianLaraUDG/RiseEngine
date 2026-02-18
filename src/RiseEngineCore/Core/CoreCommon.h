#pragma once

#include "CoreTypes.h"

// Forward declaration of concrete types.
// TODO: move this to its own file.
#include "Math/RiseMath.h"

namespace RiseEngine::Math
{
	template<typename T> struct TVector;
}

using Vector3 = RiseEngine::Math::TVector<double>;
using Vector3f = RiseEngine::Math::TVector<float>;


// Macros
#define FORCEINLINE __forceinline
#define LIKELY likely
#define UNLIKELY unlikely

// Compliation configuration macros.
#if defined(_DEBUG)
# define CORE_DEBUG 1
#endif

// TODO: implement custom Container types?