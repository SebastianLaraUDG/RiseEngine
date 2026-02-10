#include "Matrix.h"
#include <iomanip> // for setw
#include <iostream> // For printing/debugging.

namespace RiseEngine::Math
{
	template<typename T>
	__forceinline TMatrix<T>::TMatrix(const TVector<T>& VecX, const TVector<T>& VecY, const TVector<T>& VecZ, const TVector<T>& VecW)
	{
		M[0][0] = VecX.X; M[0][1] = VecX.Y; M[0][2] = VecX.Z; M[0][3] = 0.f;
		M[1][0] = VecY.X; M[1][1] = VecY.Y; M[1][2] = VecY.Z; M[1][3] = 0.f;
		M[2][0] = VecZ.X; M[2][1] = VecZ.Y; M[2][2] = VecZ.Z; M[2][3] = 0.f;
		M[3][0] = VecW.X; M[3][1] = VecW.Y; M[3][2] = VecW.Z; M[3][3] = 1.f;
	}

	/// Operators.

	template<typename T>
	TMatrix<T> Math::TMatrix<T>::operator*(const TMatrix<T>& InM) const
	{
		TMatrix result{};
		/**
		* Assuming  A is an n X p matrix
		* and B is an p X m matrix the product AB is an
		* n X m matrix.
		*/
		
		constexpr int32 p = Dimension;
		for (auto index_i = 0; index_i < Dimension; ++index_i)
		{
			for (auto index_j = 0; index_j < Dimension; ++index_j)
			{
				for (auto index_k = 0; index_k < p; ++index_k)
					result.M[index_i][index_j] += M[index_i][index_k] * InM.M[index_k][index_j];
			}
		}
		return result;
	}

	/*
	* TODO: implement with vector4 only.
	template<typename T>
	inline TVector<T> TMatrix<T>::operator*(const TVector<T>& InVec) const
	{
		return TVector<T>(
			M[0][0] * InVec.X + M[0][1] * InVec.Y + M[0][2] * InVec.Z,
			M[1][0] * InVec.X + M[1][1] * InVec.Y + M[1][2] * InVec.Z,
			M[2][0] * InVec.X + M[2][1] * InVec.Y + M[2][2] * InVec.Z
		);
	}
	*/


	template<typename T>
	TMatrix<T> Math::TMatrix<T>::MakeIdentity()
	{
		TVector<T> VecX = { T(1), T(0) , T(0) };
		TVector<T> VecY = { T(0), T(1) , T(0) };
		TVector<T> VecZ = { T(0), T(0) , T(1) };
		TVector<T> VecW = { T(0), T(0) , T(0) };
		return TMatrix(VecX, VecY, VecZ, VecW);
	}

	template<typename T>
	void TMatrix<T>::Print(const char* name) const
	{
		std::cout << name << ":\n";

		for (int i = 0; i < 4; ++i)
		{
			std::cout << "[ ";
			for (int j = 0; j < 4; ++j)
			{
				std::cout << std::setw(8) << M[i][j] << " ";
			}
			std::cout << "]\n";
		}
	}

	// Calculated using Laplace Expansion by means of the Cayley-Hamilton Theorem.
	template<typename T>
	T TMatrix<T>::Determinant() const
	{
		// Calculate the determinants of the 2x2 sub-matrices of the first two rows.
		// Then combine them with the determinants of the last two rows.
		const T top_01 = M[0][0] * M[1][1] - M[0][1] * M[1][0];
		const T top_02 = M[0][0] * M[1][2] - M[0][2] * M[1][0];
		const T top_03 = M[0][0] * M[1][3] - M[0][3] * M[1][0];
		const T top_12 = M[0][1] * M[1][2] - M[0][2] * M[1][1];
		const T top_13 = M[0][1] * M[1][3] - M[0][3] * M[1][1];
		const T top_23 = M[0][2] * M[1][3] - M[0][3] * M[1][2];

		// Calculate the determinants of the 2x2 sub-matrices of the last two rows.
		const T bottom_01 = M[2][0] * M[3][1] - M[2][1] * M[3][0];
		const T bottom_02 = M[2][0] * M[3][2] - M[2][2] * M[3][0];
		const T bottom_03 = M[2][0] * M[3][3] - M[2][3] * M[3][0];
		const T bottom_12 = M[2][1] * M[3][2] - M[2][2] * M[3][1];
		const T bottom_13 = M[2][1] * M[3][3] - M[2][3] * M[3][1];
		const T bottom_23 = M[2][2] * M[3][3] - M[2][3] * M[3][2];

		// The determinant of the 4x4 matrix is obteined by alternating sum
		// of the products of the determinants of the opposite 2x2 blocks.
		return
			(top_01 * bottom_23 -
			top_02 * bottom_13 +
			top_03 * bottom_12 +
			top_12 * bottom_03 -
			top_13 * bottom_02 +
			top_23 * bottom_01);
	};
} // namespace RiseEngine