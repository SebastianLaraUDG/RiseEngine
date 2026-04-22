#pragma once

/**
* TODO: currently tolerance is implemented only in Vector.h
* in IsNormalized().
*/

// Collection of all math-related libraries.
#include "Public/Vector.h"
#include "Public/Matrix.h"

// Forward declaration of concrete types.
namespace RiseEngine::Math
{
	template<typename T> struct TVector;
}

using Vector3 = RiseEngine::Math::TVector<f64>;
using Vector3f = RiseEngine::Math::TVector<f32>;

using Matrix4 = RiseEngine::Math::TMatrix<f64>;
using Matrix4f = RiseEngine::Math::TMatrix<f32>;