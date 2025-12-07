#pragma once
#include <type_traits>
#include <RiseEngineCore/Core.h>


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
			* TODO: create statics: ZeroVector, OneVector, XAxis, YAxis, ZAxis. Also Up, Dowm, Forward, Backwards, Right, Left.
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

			/// <summary>
			/// Calculate the cross product of two vectors.
			/// </summary>
			/// <param name="A">First vector.</param>
			/// <param name="B">Second Vector.</param>
			/// <returns>The cross product between them.</returns>
			[[nodiscard]] __forceinline static TVector<T> CrossProduct(const TVector<T>& A, const TVector<T>& B);

			/// <summary>
			/// Calculate the dot product of two vectors.
			/// </summary>
			/// <param name="A">First vector.</param>
			/// <param name="B">Second Vector.</param>
			/// <returns>The dot product between them.</returns>
			[[nodiscard]] __forceinline static TVector<T> DotProduct(const TVector<T>& A, const TVector<T>& B);

			/*
			* Operators.
			*/
			[[nodiscard]] __forceinline TVector<T>operator+(const TVector<T>& V) const;
		};
		
	}
}