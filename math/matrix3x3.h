#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <cstring>
#include "math/vector.h"

typedef double REAL;
template<typename T = REAL>
struct mat3
{
    mat3<T>(T _00 = 0, T _01 = 0, T _02 = 0,
            T _10 = 0, T _11 = 0, T _12 = 0,
            T _20 = 0, T _21 = 0, T _22 = 0) {
        data[0] = _00;  data[1] = _01;  data[2] = _02;
        data[3] = _10;  data[4] = _11;  data[5] = _12;
        data[6] = _20;  data[7] = _21;  data[8] = _22;
    }

    mat3<T>(const T *copy) { memcpy(data, copy, sizeof(T) * 9); }

    inline Vector3 operator*(const Vector3 &rhs) const {
        return Vector3(a*rhs.x + b*rhs.y + c*rhs.z,
                       d*rhs.x + e*rhs.y + f*rhs.z,
                       g*rhs.x + h*rhs.y + i*rhs.z);
    }

    inline mat3 operator*(const mat3 &rhs) {
        return mat3(a*rhs.a + b*rhs.d + c*rhs.g,
                    a*rhs.b + b*rhs.e + c*rhs.h,
                    a*rhs.c + b*rhs.f + c*rhs.i,
                    d*rhs.a + e*rhs.d + f*rhs.g,
                    d*rhs.b + e*rhs.e + f*rhs.h,
                    d*rhs.c + e*rhs.f + f*rhs.i,
                    g*rhs.a + h*rhs.d + i*rhs.g,
                    g*rhs.b + h*rhs.e + i*rhs.h,
                    g*rhs.c + h*rhs.f + i*rhs.i);
    }

    union {
        T data[9];
        struct {
            T a, b, c,
              d, e, f,
              g, h, i;
        };
    };
};

typedef mat3<REAL> Matrix3x3;
#include "matrix3x3.inl"

#endif // MATRIX3X3_H
