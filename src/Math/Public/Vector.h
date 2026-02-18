#pragma once
#include <type_traits>

#include "RiseEngineCore/Core/Core.h"//  TODO: Keep this for DLLs?
#include "RiseEngineCore/Core/CoreCommon.h"

namespace RiseEngine
{
	namespace Math
	{
		template<typename T>
		struct TVector
		{
			static_assert(std::is_floating_point_v<T>, "T must be floating point.");

		public:
			union
			{
				struct
				{
					T X;
					T Y;
					T Z;
				};
			};
			static constexpr int32 NumComponents = 3;
			/*
			* TODO: create statics: OneVector, XAxis, YAxis, ZAxis. Also Up, Dowm, Forward, Backwards, Right, Left.
			* TODO: Define all direction vectors once I define the worlds directions.
			* TODO: define all previous for both float and double.
			*/

			/// <summary>
			/// Default constructor (no initialization).
			/// </summary>
			[[nodiscard]] TVector() = default;

			/// <summary>
			/// Initialize all components to a single T value.
			/// </summary>
			/// <param name="InF">Value to set all components to.</param>
			[[nodiscard]] explicit __forceinline TVector(T InF);

			/// <summary>
			/// Constructor using initial values for each component.
			/// </summary>
			/// <param name="x">X  coordinate.</param>
			/// <param name="y">Y  coordinate.</param>
			/// <param name="z">Z  coordinate.</param>
			[[nodiscard]] __forceinline TVector(T x, T y, T z);

			/**
			* Operators.
			*/
			[[nodiscard]] __forceinline TVector<T>operator +(const TVector<T>& V) const;
			[[nodiscard]] __forceinline TVector<T>operator -(const TVector<T>& V) const;
			[[nodiscard]] __forceinline TVector<T>operator *(T s) const;
			[[nodiscard]] TVector<T>operator /(T s) const;
			TVector<T>& operator *=(T s);
			TVector<T>& operator /=(T s);


			[[nodiscard]] __forceinline T Magnitude() const;
			
			/// @brief Returns the same as Magnitude();
			/// @return Length of a Vector.
			[[nodiscard]] __forceinline T Size() const;

			/// @brief Returns the same as Magnitude();
			/// @return Length of a Vector.
			[[nodiscard]] __forceinline T Length() const;

			[[nodiscard]] __forceinline TVector<T> GetNormal() const;

			__forceinline bool IsNormalized(T tolerance = (T)0.0001) const;

			/// @brief Normalize this vector.
			/// @return The current vector with a magnitude of 1 (unit vector), or the same vector if magnitude is zero.
			TVector<T>& Normalize();

			/// <summary>
			/// Calculate the cross product of two vectors.
			/// </summary>
			/// <param name="A">First vector.</param>
			/// <param name="B">Second Vector.</param>
			/// <returns>The cross product between them.</returns>
			[[nodiscard]] __forceinline static TVector<T> CrossProduct(const TVector<T>& A, const TVector<T>& B);

			/**
			* @brief Calculate the dot product of two vectors.
			* 
			* If the vectors are normalized, the result is in [-1, 1]:
			* -1 meaning: vectors are opposite
			* 0 meaning: vectors are perpendicular
			* 1 meaning: vectors are parallel and point in the same direction
			* 
			* @param The first vector. Preferably normalized.
			* @param The second vector. Preferably normalized.
			* @return The dot product between the two vectors.
			*/
			[[nodiscard]] __forceinline static T DotProduct(const TVector<T>& A, const TVector<T>& B);

			/**
			* @brief The absolute value of the scalar
			triple product represents the volume of
			the parallelepiped formed by the three vectors.
			|a DOT (b x c)|
			@param A
			@param B
			@param C
			@return The absolute value of the scalar triple product.
			*/
			[[nodiscard]] __forceinline static T ScalarTripleProduct(const TVector<T>& A, const TVector<T>& B, const TVector<T>& C);

			/**
			* @brief Make the projection of A onto B.
			* @param The first vector.
			* @param The second vector. Normalized for faster processing.
			* @return A vector that satisfies the A projection onto B math operation.
			*/
			[[nodiscard]] __forceinline static TVector<T> Project(const TVector<T>& A, const TVector<T>& B);
			
			/**
			* @brief Make the rejection of A from B.
			* @param The first vector.
			* @param The second vector. Normalized for faster processing.
			* @return A vector that satisfies the A rejection from B math operation.
			*/
			[[nodiscard]] __forceinline static TVector<T> Reject(const TVector<T>& A, const TVector<T>& B);

			[[nodiscard]] __forceinline static TVector<T> ZeroVector();
			[[nodiscard]] __forceinline static TVector<T> OneVector();

			[[nodiscard]] __forceinline static TVector<T> UnitVectorX();
			[[nodiscard]] __forceinline static TVector<T> UnitVectorY();
			[[nodiscard]] __forceinline static TVector<T> UnitVectorZ();
		};
		
	}
}
#include "Vector.inl"