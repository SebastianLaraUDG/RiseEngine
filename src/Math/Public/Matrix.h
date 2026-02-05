#pragma once

#include <type_traits>
#include "Vector.h"

namespace RiseEngine::Math
{

	/// @brief 4X4 Matrix. Row-major.
	template<typename T>
	struct alignas(16) TMatrix
	{
		static_assert(std::is_floating_point_v<T>, "T must be floating point.");

	public:
		using FReal = T;

		alignas(16) T M[4][4];

		/// @brief Represents the length of each dimension (row and column).
		static constexpr int32 Dimension = 4;

		// Constructors.

		TMatrix() = default;
		
		// Version that takes 4 vectors.
		__forceinline TMatrix(const TVector<T>& VecX, const TVector<T>& VecY, const TVector<T>& VecZ, const TVector<T>& VecW);
		
		/// Operators.
		[[nodiscard]] TMatrix<T> operator *(const TMatrix<T>& OtherMatrix) const;
		
// TODO: do only with Vector4[[nodiscard]] TVector<T> operator *(const TVector<T>& InVec) const;

		// Construct an identity matrix.
		static TMatrix<T> MakeIdentity();

		/// <summary>
		/// Print the whole matrix.
		/// </summary>
		/// <param name="name">A string to identify the matrix on screen. For example the matrix name.</param>
		void Print(const char* name = "Printing Matrix... Insert name.\n") const;
	};

}

#include "Matrix.inl"