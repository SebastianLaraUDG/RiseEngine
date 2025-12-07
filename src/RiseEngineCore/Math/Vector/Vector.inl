#include "Vector.h"
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
        inline TVector<T> TVector<T>::CrossProduct(const TVector<T>& A, const TVector<T>& B)
        {
            return TVector(
                A.y * B.z - B.y * A.z,
                A.z * B.x - B.z * A.x,
                A.x * B.y - B.x * A.y
            );
        }


        template<typename T>
        inline TVector<T> TVector<T>::DotProduct(const TVector<T>& A, const TVector<T>& B)
        {
            return TVector<T>();    // TODO:
        }

        template<typename T>
        inline TVector<T> TVector<T>::operator+(const TVector<T>& V) const
        {
            return TVector<T>(X + V.X, Y + V.Y, Z + V.Z);
        }
    }
}