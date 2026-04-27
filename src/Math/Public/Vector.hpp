#pragma once
#include <type_traits>
#include <iostream>
#include <RiseEngineCore/Core/CoreTypes.hpp>

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
			static constexpr T DefaultTolerance = static_cast<T>(1.e-6);
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
			[[nodiscard]] explicit inline TVector(T InF);

			/// <summary>
			/// Constructor using initial values for each component.
			/// </summary>
			/// <param name="x">X  coordinate.</param>
			/// <param name="y">Y  coordinate.</param>
			/// <param name="z">Z  coordinate.</param>
			[[nodiscard]] inline TVector(T x, T y, T z);

			/**
			* Operators.
			*/
			[[nodiscard]] inline TVector<T>operator +(const TVector<T>& V) const;
			[[nodiscard]] inline TVector<T>operator -(const TVector<T>& V) const;
			[[nodiscard]] inline TVector<T>operator *(T s) const;
			[[nodiscard]] TVector<T>operator /(T s) const;
			TVector<T>& operator *=(T s);
			TVector<T>& operator /=(T s);
			[[nodiscard]] inline TVector<T>operator -() const;
			inline bool operator ==(const TVector<T>& Other) const;
			inline bool operator !=(const TVector<T>& Other) const;
			inline bool Equals(const TVector<T>& Other, const T Tolerance = DefaultTolerance) const;

			// TODO: remove when tests pass.
			friend std::ostream& operator<<(std::ostream& os, const TVector<T>& V)
			{
				return os << "TVector(X=" << V.X << ", Y=" << V.Y << ", Z=" << V.Z << ")";
			}

			[[nodiscard]] inline T Magnitude() const;
			/*
			* @brief An optimized alternative to Magnitude if you do not need to perform the square root.
			*/
			[[nodiscard]] inline T SquaredMagnitude() const;
			
			/// @brief Returns the same as Magnitude();
			/// @return Length of a Vector.
			[[nodiscard]] inline T Size() const;

			/// @brief Returns the same as Magnitude();
			/// @return Length of a Vector.
			[[nodiscard]] inline T Length() const;

			// @return Will return ZeroVector if magnitud equals zero.
			[[nodiscard]] inline TVector<T> GetNormal() const;

			inline bool IsNormalized(T tolerance = (T)0.0001) const;

			/// @brief Normalize this vector.
			/// @return The current vector with a magnitude of 1 (unit vector), or the same vector if magnitude is zero.
			TVector<T>& Normalize();

			/// <summary>
			/// Calculate the cross product of two vectors.
			/// </summary>
			/// <param name="A">First vector.</param>
			/// <param name="B">Second Vector.</param>
			/// <returns>The cross product between them.</returns>
			[[nodiscard]] inline static TVector<T> CrossProduct(const TVector<T>& A, const TVector<T>& B);

			/**
			* @brief Calculate the dot product of two vectors.
			* 
			* If the vectors are normalized, the result is in [-1, 1]:
			* -1 meaning: vectors are opposite.
			* 0 meaning: vectors are perpendicular (90 degrees between them).
			* 1 meaning: vectors are parallel and point in the same direction.
			* 
			* If A Dot B > 0 the angle between them is less than 90 degrees.
			* If A Dot B < 0 the angle between them is greater than 90 degrees.
			* 
			* @param The first vector. Preferably normalized.
			* @param The second vector. Preferably normalized.
			* @return The dot product between the two vectors.
			*/
			[[nodiscard]] inline constexpr static T DotProduct(const TVector<T>& A, const TVector<T>& B);

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
			[[nodiscard]] inline static T ScalarTripleProduct(const TVector<T>& A, const TVector<T>& B, const TVector<T>& C);

			/**
			* @brief Make the projection of A onto B.
			* @param The first vector.
			* @param The second vector. Normalized for faster processing.
			* @return A vector that satisfies the A projection onto B math operation.
			*/
			[[nodiscard]] inline static TVector<T> Project(const TVector<T>& A, const TVector<T>& B);
			
			/**
			* @brief Make the rejection of A from B.
			* @param The first vector.
			* @param The second vector. Normalized for faster processing.
			* @return A vector that satisfies the A rejection from B math operation.
			*/
			[[nodiscard]] inline static TVector<T> Reject(const TVector<T>& A, const TVector<T>& B);

			/**
			* @brief Calculate the distance between two vectors. You can also use DistanceSquared if you
			* don't need to calculate the square root.
			*/
			[[nodiscard]] static constexpr T Distance(const TVector<T>& A, const TVector<T>& B);

			/**
			* Calculate the distance between two vectors without computing the square root.
			*/
			[[nodiscard]] static constexpr T DistanceSquared(const TVector<T>& A, const TVector<T>& B);

			[[nodiscard]] static constexpr T FindAngle(const TVector<T>& A, const TVector<T>& B); // TODO: this returns the cos of the angle but calculating acos is not very optimal.

			[[nodiscard]] inline static TVector<T> ZeroVector();
			[[nodiscard]] inline static TVector<T> OneVector();
			
			[[nodiscard]] inline static TVector<T> ForwardVector();
			[[nodiscard]] inline static TVector<T> UpVector();
			[[nodiscard]] inline static TVector<T> RightVector();
			
			[[nodiscard]] inline static TVector<T> UnitVectorX();
			[[nodiscard]] inline static TVector<T> UnitVectorY();
			[[nodiscard]] inline static TVector<T> UnitVectorZ();
		};
		
	}
}
#include "Vector.inl"