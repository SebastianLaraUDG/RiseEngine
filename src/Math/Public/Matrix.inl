#include "Matrix.h"
#include <iomanip> // for setw
#include <iostream> // For printing/debugging.
#include <cmath>

namespace RiseEngine::Math
{
	// Each vector corresponds to a row (VecX = row 0).
	template<typename T>
	__forceinline TMatrix<T>::TMatrix(const TVector<T>& Line0, const TVector<T>& Line1, const TVector<T>& Line2, const TVector<T>& Line3)
	{
		M[0][0] = Line0.X; M[0][1] = Line0.Y; M[0][2] = Line0.Z; M[0][3] = 0.f;
		M[1][0] = Line1.X; M[1][1] = Line1.Y; M[1][2] = Line1.Z; M[1][3] = 0.f;
		M[2][0] = Line2.X; M[2][1] = Line2.Y; M[2][2] = Line2.Z; M[2][3] = 0.f;
		M[3][0] = Line3.X; M[3][1] = Line3.Y; M[3][2] = Line3.Z; M[3][3] = 1.f;
	}

	// Each vector corresponds to a row (VecX = row 0).
	template<typename T>
	inline TMatrix<T>::TMatrix(const TVector<T>& Line0, const TVector<T>& Line1, const TVector<T>& Line2, const TVector<T>& Line3, T m03, T m13, T m23, T m33)
	{
		M[0][0] = Line0.X; M[0][1] = Line0.Y; M[0][2] = Line0.Z; M[0][3] = m03;
		M[1][0] = Line1.X; M[1][1] = Line1.Y; M[1][2] = Line1.Z; M[1][3] = m13;
		M[2][0] = Line2.X; M[2][1] = Line2.Y; M[2][2] = Line2.Z; M[2][3] = m23;
		M[3][0] = Line3.X; M[3][1] = Line3.Y; M[3][2] = Line3.Z; M[3][3] = m33;
	}

	// Operators.

	template<typename T>
	TMatrix<T> TMatrix<T>::operator*(const TMatrix<T>& InM) const
	{
		TMatrix result{};
		/**
		* Assuming  A is an n X p matrix
		* and B is an p X m matrix the product AB is an
		* n X m matrix.
		*/

		constexpr int32 p = Dimension;
		for (int32 index_i = 0; index_i < Dimension; ++index_i)
		{
			for (int32 index_j = 0; index_j < Dimension; ++index_j)
			{
				for (int32 index_k = 0; index_k < p; ++index_k)
				{
					result.M[index_i][index_j] += M[index_i][index_k] * InM.M[index_k][index_j];
				}
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
	TMatrix<T> TMatrix<T>::MakeIdentity()
	{
		TVector<T> VecX = { T(1), T(0) , T(0) };
		TVector<T> VecY = { T(0), T(1) , T(0) };
		TVector<T> VecZ = { T(0), T(0) , T(1) };
		TVector<T> VecW = { T(0), T(0) , T(0) };
		return TMatrix(VecX, VecY, VecZ, VecW);
	}

	template<typename T>
	TMatrix<T> TMatrix<T>::Zero()
	{
		const TVector<T> VecZero = TVector<T>::ZeroVector();
		constexpr T zero = static_cast<T>(0);
		return TMatrix(VecZero, VecZero, VecZero, VecZero, zero, zero, zero, zero); // TODO: could be written in a cleaner way.
	}

	template<typename T>
	TMatrix<T> TMatrix<T>::MakeRotation(T InRotationX, T InRotationY, T InRotationZ)
	{
		return MakeRotationX(InRotationX) * MakeRotationY(InRotationY) * MakeRotationZ(InRotationZ);
	}

	template<typename T>
	TMatrix<T> TMatrix<T>::MakeRotation(const T rotation, const TVector<T>& axis)
	{
		const T coseno = cos(rotation);
		const T seno = sin(rotation);
		const T d = static_cast<T>(1 - coseno);
		const T x = axis.X * d;
		const T y = axis.Y * d;
		const T z = axis.Z * d;
		const T axay = x * axis.Y;
		const T axaz = x * axis.Z;
		const T ayaz = y * axis.Z;

		const TVector<T> row0 = { coseno + x * axis.X, axay - seno * axis.Z, axaz + seno * axis.Y };
		const TVector<T> row1 = { axay + seno * axis.Z, coseno + y * axis.Y, ayaz - seno * axis.X };
		const TVector<T> row2 = { axaz - seno * axis.Y, ayaz + seno * axis.X, coseno + z * axis.Z };

		return TMatrix<T>(row0, row1, row2, TVector<T>::ZeroVector());
	}

	template<typename T>
	TMatrix<T> TMatrix<T>::MakeRotationX(T InAngle)
	{
		const T c = std::cos(InAngle);
		const T s = std::sin(InAngle);

		const TVector<T> line0 = { static_cast<T>(1), static_cast<T>(0), static_cast<T>(0) };
		const TVector<T> line1 = { static_cast<T>(0),		c,			-s };
		const TVector<T> line2 = { static_cast<T>(0),		s,			 c };
		const TVector<T> zero = TVector<T>::ZeroVector();
		// Last column is 0,0,0,1.
		return TMatrix<T>(line0, line1, line2, zero);
	}

	template<typename T>
	TMatrix<T> TMatrix<T>::MakeRotationY(T InAngle)
	{
		const T c = std::cos(InAngle);
		const T s = std::sin(InAngle);

		const TVector<T> line0 = {		c,			  static_cast<T>(0),		s };
		const TVector<T> line1 = { static_cast<T>(0), static_cast<T>(1),		static_cast<T>(0) };
		const TVector<T> line2 = {		-s,			  static_cast<T>(0),		c};
		const TVector<T> zero = TVector<T>::ZeroVector();
		// Last column is 0,0,0,1.
		return TMatrix<T>(line0, line1, line2, zero);
	}

	template<typename T>
	TMatrix<T> TMatrix<T>::MakeRotationZ(T InAngle)
	{
		const T c = std::cos(InAngle);
		const T s = std::sin(InAngle);

		const TVector<T> line0 = { c,					   -s,				static_cast<T>(0) };
		const TVector<T> line1 = { s,						c,				static_cast<T>(0) };
		const TVector<T> line2 = { static_cast<T>(0), static_cast<T>(0),	static_cast<T>(1) };
		const TVector<T> zero = TVector<T>::ZeroVector();
		// Last column is 0,0,0,1.
		return TMatrix<T>(line0, line1, line2, zero);
	}

	template<typename T>
	void TMatrix<T>::Print(const char* name) const
	{
		std::cout << name << ":\n";

		for (int i = 0; i < Dimension; ++i)
		{
			std::cout << "[ ";
			for (int j = 0; j < Dimension; ++j)
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

	template<typename T>
	TMatrix<T> TMatrix<T>::Inverse() const
	{
		// 2x2 sub-determinants para las primeras dos filas
		const T s0 = M[0][0] * M[1][1] - M[0][1] * M[1][0];
		const T s1 = M[0][0] * M[1][2] - M[0][2] * M[1][0];
		const T s2 = M[0][0] * M[1][3] - M[0][3] * M[1][0];
		const T s3 = M[0][1] * M[1][2] - M[0][2] * M[1][1];
		const T s4 = M[0][1] * M[1][3] - M[0][3] * M[1][1];
		const T s5 = M[0][2] * M[1][3] - M[0][3] * M[1][2];

		// 2x2 sub-determinants para las ultimas dos filas
		const T c0 = M[2][0] * M[3][1] - M[2][1] * M[3][0];
		const T c1 = M[2][0] * M[3][2] - M[2][2] * M[3][0];
		const T c2 = M[2][0] * M[3][3] - M[2][3] * M[3][0];
		const T c3 = M[2][1] * M[3][2] - M[2][2] * M[3][1];
		const T c4 = M[2][1] * M[3][3] - M[2][3] * M[3][1];
		const T c5 = M[2][2] * M[3][3] - M[2][3] * M[3][2];

		const T det = s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0;

		// Si el determinante es cercano a cero, retornamos matriz nula (Zero Matrix)
		if (std::abs(det) <= static_cast<T>(1e-6))
		{
			const TVector<T> zero = TVector<T>::ZeroVector();
			return TMatrix<T>(zero, zero, zero, zero);
		}

		const T invDet = static_cast<T>(1) / det;

		TMatrix<T> res;

		// Row 0
		res.M[0][0] = (M[1][1] * c5 - M[1][2] * c4 + M[1][3] * c3) * invDet;
		res.M[0][1] = (-M[0][1] * c5 + M[0][2] * c4 - M[0][3] * c3) * invDet;
		res.M[0][2] = (M[3][1] * s5 - M[3][2] * s4 + M[3][3] * s3) * invDet;
		res.M[0][3] = (-M[2][1] * s5 + M[2][2] * s4 - M[2][3] * s3) * invDet;

		// Row 1
		res.M[1][0] = (-M[1][0] * c5 + M[1][2] * c2 - M[1][3] * c1) * invDet;
		res.M[1][1] = (M[0][0] * c5 - M[0][2] * c2 + M[0][3] * c1) * invDet;
		res.M[1][2] = (-M[3][0] * s5 + M[3][2] * s2 - M[3][3] * s1) * invDet;
		res.M[1][3] = (M[2][0] * s5 - M[2][2] * s2 + M[2][3] * s1) * invDet;

		// Row 2
		res.M[2][0] = (M[1][0] * c4 - M[1][1] * c2 + M[1][3] * c0) * invDet;
		res.M[2][1] = (-M[0][0] * c4 + M[0][1] * c2 - M[0][3] * c0) * invDet;
		res.M[2][2] = (M[3][0] * s4 - M[3][1] * s2 + M[3][3] * s0) * invDet;
		res.M[2][3] = (-M[2][0] * s4 + M[2][1] * s2 - M[2][3] * s0) * invDet;

		// Fila 3
		res.M[3][0] = (-M[1][0] * c3 + M[1][1] * c1 - M[1][2] * c0) * invDet;
		res.M[3][1] = (M[0][0] * c3 - M[0][1] * c1 + M[0][2] * c0) * invDet;
		res.M[3][2] = (-M[3][0] * s3 + M[3][1] * s1 - M[3][2] * s0) * invDet;
		res.M[3][3] = (M[2][0] * s3 - M[2][1] * s1 + M[2][2] * s0) * invDet;

		return res;
	}

	template<typename T>
	inline TMatrix<T> TMatrix<T>::Transpose() const
	{
		TMatrix transpose{};
		transpose.M[0][0] = M[0][0]; transpose.M[0][1] = M[1][0]; transpose.M[0][2] = M[2][0]; transpose.M[0][3] = M[3][0];
		transpose.M[1][0] = M[0][1]; transpose.M[1][1] = M[1][1]; transpose.M[1][2] = M[2][1]; transpose.M[1][3] = M[3][1];
		transpose.M[2][0] = M[0][2]; transpose.M[2][1] = M[1][2]; transpose.M[2][2] = M[2][2]; transpose.M[2][3] = M[3][2];
		transpose.M[3][0] = M[0][3]; transpose.M[3][1] = M[1][3]; transpose.M[3][2] = M[2][3]; transpose.M[3][3] = M[3][3];
		return transpose;
	}

	template<typename T>
	bool TMatrix<T>::Equals(const TMatrix<T>& Other, const T tolerance) const
	{
		for (int32 index_i = 0; index_i < Dimension; ++index_i)
		{
			for (int32 index_j = 0; index_j < Dimension; ++index_j)
			{
				// Exceeded tolerance.
				if (std::abs(M[index_i][index_j] - Other.M[index_i][index_j]) > tolerance)
					return false;
			}
		}
		return true;
	}

	template<typename T>
	bool TMatrix<T>::IsOrthogonal(const T tolerance) const
	{
		const TMatrix<T> Inverse = this->Inverse();
		const TMatrix<T> Transpose = this->Transpose();

		return Inverse.Equals(Transpose, tolerance);
	}
} // namespace RiseEngine