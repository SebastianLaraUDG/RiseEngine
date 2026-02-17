#include "Vector.h"
#include <cmath>
namespace RiseEngine
{
    namespace Math
    {
        template<typename T>
        inline TVector<T>::TVector(T InF)
            : X(InF), Y(InF), Z(InF)
        {
        }

        template<typename T>
        inline TVector<T>::TVector(T x, T y, T z)
            : X(x), Y(y), Z(z)
        {
        }

        
        template<typename T>
        inline TVector<T> TVector<T>::operator+(const TVector<T>& V) const
        {
            return TVector<T>(X + V.X, Y + V.Y, Z + V.Z);
        }

        template<typename T>
        inline TVector<T> TVector<T>::operator-(const TVector<T>& V) const
        {
            return TVector<T>(X - V.X, Y - V.Y, Z - V.Z);
        }

        template<typename T>
        inline TVector<T> TVector<T>::operator*(T s) const
        {
            return TVector<T>(X * s, Y * s, Z * s);
        }
        
        template<typename T>
        TVector<T> TVector<T>::operator/(T s) const
        {
            s = 1.f / s;
            return TVector<T>(X * s, Y * s, Z * s);
        }

        template <typename T>
        TVector<T> &TVector<T>::operator*=(T s)
        {
            X *= s;
            Y *= s;
            Z *= s;
            return (*this);
        }

        template <typename T>
        TVector<T> &TVector<T>::operator/=(T s)
        {
            s = 1.f / s;
            X *= s;
            Y *= s;
            Z *= s;
            return (*this);
        }

        template <typename T>
        inline T TVector<T>::Magnitude() const
        {
            return sqrt(X * X + Y * Y + Z * Z);
        }

        template <typename T>
        inline T TVector<T>::Size() const
        {
            return Magnitude();
        }

        template <typename T>
        inline T TVector<T>::Length() const
        {
           return Magnitude();
        }
        
        template <typename T>
        inline TVector<T> TVector<T>::GetNormal() const
        {
            return *this / Magnitude();
        }

        template<typename T>
        inline bool TVector<T>::IsNormalized(T tolerance) const
        {
			const T magnitudeSquared = X * X + Y * Y + Z * Z;
            const T one = (T)1;
            return (magnitudeSquared > one - tolerance) && (magnitudeSquared < one + tolerance);
        }

		template <typename T>
		TVector<T>& TVector<T>::Normalize()
		{
			const T mag = Magnitude();
			if (mag != T(0))
			{
				*this /= mag;
			}
            
            return *this;
		}


        template<typename T>
        inline TVector<T> TVector<T>::CrossProduct(const TVector<T>& A, const TVector<T>& B)
        {
            return TVector(
                A.Y * B.Z - B.Y * A.Z,
                A.Z * B.X - B.Z * A.X,
                A.X * B.Y - B.X * A.Y
            );
        }


        template<typename T>
        inline T TVector<T>::DotProduct(const TVector<T>& A, const TVector<T>& B)
        {
			return A.X * B.X + A.Y * B.Y + A.Z * B.Z;
        }

        template<typename T>
        inline T TVector<T>::ScalarTripleProduct(const TVector<T>& A, const TVector<T>& B, const TVector<T>& C)
        {
            return static_cast<T>(
                std::abs( DotProduct(A, CrossProduct(B, C)) )
                );
        }

        template<typename T>
        inline TVector<T> TVector<T>::Project(const TVector<T>& A, const TVector<T>& B)
        {
            // The dot product of normalized B equals 1.
            // Knowing that, it is obvious that dividing is unnecessary.
            if (B.IsNormalized())
            {
                return B * DotProduct(A, B);
            }
            return (B * (DotProduct(A, B) / DotProduct(B, B)));
        }

        template<typename T>
        inline TVector<T> TVector<T>::Reject(const TVector<T>& A, const TVector<T>& B)
        {
            // The dot product of normalized B equals 1.
            // Knowing that, it is obvious that dividing is unnecessary.
            return A - Project(A, B);
        }

        template<typename T>
        inline TVector<T> TVector<T>::ZeroVector()
        {
            return TVector(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
        }

        template<typename T>
        inline TVector<T> TVector<T>::UnitVectorX()
        {
            return TVector((T)1, (T)0, (T)0);
        }

        template<typename T>
        inline TVector<T> TVector<T>::UnitVectorY()
        {
            return TVector((T)0, (T)1, (T)0);
        }

        template<typename T>
        inline TVector<T> TVector<T>::UnitVectorZ()
        {
			return TVector((T)0, (T)0, (T)1);
        }
    }
}