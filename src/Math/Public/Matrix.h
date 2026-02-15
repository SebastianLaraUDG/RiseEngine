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

		// Version that takes 4 vectors and 4 values for the fourth column.
		__forceinline TMatrix(const TVector<T>& VecX, const TVector<T>& VecY, const TVector<T>& VecZ, const TVector<T>& VecW, T m03, T m13, T m23, T m33);
		
		// Operators.
		[[nodiscard]] TMatrix<T> operator *(const TMatrix<T>& OtherMatrix) const;

		
// TODO: do only with Vector4[[nodiscard]] TVector<T> operator *(const TVector<T>& InVec) const;

		/**
		* @internal The determinant is equal to the hypervolume of the n-dimensional parallelotope formed by those vectors, 
			and it can be positive or negative depending on the orientation of the vectors.
			A matrix has an inverse if and only if its determinant is not zero.
		*/
		[[nodiscard]] T Determinant() const;

		// Matrix adjugate (TODO: confirm comment is correct).
		// Please note that to get the inverse of a matrix, mathematically speaking,
		// the determinant must be non-zero.
		// This function returns a Zero matrix if the determinant equals zero.
		[[nodiscard]] TMatrix<T> Inverse() const;

		// Get the transpose version of the current matrix.
		[[nodiscard]] inline TMatrix<T> Transpose() const;

		// Construct an identity matrix.
		static TMatrix<T> MakeIdentity();
		
		// Construct a matrix whose elements are all zeros.
		static TMatrix<T> Zero();

		/// <summary>
		/// Print the whole matrix.
		/// </summary>
		/// <param name="name">A string to identify the matrix on screen. For example the matrix name.</param>
		void Print(const char* name = "Printing Matrix... Insert name.\n") const;
	};

}

#include "Matrix.inl"