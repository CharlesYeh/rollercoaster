/*!
   @file   CS123Matrix.cpp
   @author Travis Fischer (fisch0920@gmail.com)
   @date   Fall 2008
   
   @brief
      Provides basic functionality for a templated, arbitrarily-sized matrix.
      You will need to fill this file in for the Camtrans assignment.

**/

// CS123Matrix.h can be found in /course/cs123/include/algebra
#include <CS123Matrix.h>
#include <iostream>

//@name Routines which generate specific-purpose transformation matrices
//@{---------------------------------------------------------------------
// @returns the scale matrix described by the vector
using namespace std;
Matrix4x4 getScaleMat(const Vector4 &v) {
    Matrix4x4 scaleMat = Matrix4x4(v.x, 0, 0, 0,
                                   0, v.y, 0 ,0,
                                   0, 0, v.z, 0,
                                   0, 0, 0, 1);
    return scaleMat;
}

// @returns the translation matrix described by the vector
Matrix4x4 getTransMat(const Vector4 &v) {
    Matrix4x4 transMat = Matrix4x4(1, 0, 0, v.x,
                                   0, 1, 0, v.y,
                                   0, 0, 1, v.z,
                                   0, 0, 0, 1);
    return transMat;
}

// @returns the rotation matrix about the x axis by the specified angle
Matrix4x4 getRotXMat (const REAL radians) {
    REAL cosVal = cos(radians);
    REAL sinVal = sin(radians);
    Matrix4x4 rotXMat = Matrix4x4(1, 0, 0, 0,
                                   0, cosVal, -sinVal, 0,
                                   0, sinVal, cosVal, 0,
                                   0, 0, 0, 1);
    return rotXMat;
}

// @returns the rotation matrix about the y axis by the specified angle
Matrix4x4 getRotYMat (const REAL radians) {
    REAL cosVal = cos(radians);
    REAL sinVal = sin(radians);
    Matrix4x4 rotYMat = Matrix4x4(cosVal, 0, sinVal, 0,
                                  0, 1, 0, 0,
                                  -sinVal, 0, cosVal, 0,
                                  0, 0, 0, 1);
    return rotYMat;
}

// @returns the rotation matrix about the z axis by the specified angle
Matrix4x4 getRotZMat (const REAL radians) {
    REAL cosVal = cos(radians);
    REAL sinVal = sin(radians);
    Matrix4x4 rotZMat = Matrix4x4(cosVal, -sinVal, 0, 0,
                                  sinVal, cosVal, 0, 0,
                                  0, 0, 1, 0,
                                  0, 0, 0, 1);
    return rotZMat;
}

// @returns the rotation matrix around the vector and point by the specified angle
Matrix4x4 getRotMat  (const Vector4 &p, const Vector4 &v, const REAL a) {
    //theta = atan2(az,ax)
    //phi = -atan2(ay, sqrt(ax^2 + az^2)
    //M1 = getRotYMat(theta), m2 = getRotZMat(phi),
    //p` = M1^-1 * M2^-1 * M-3 * M2 * M1 * p

    Matrix4x4 MT1 = getInvTransMat(p); //translate to origin
    Matrix4x4 MT2 = getTransMat(p); //translate back
    REAL angle1 = atan2(v.z, v.x);
    REAL angle2 = -1 * atan2(v.y, sqrt((v.x * v.x) + (v.z * v.z)));
    Matrix4x4 M1 = getRotYMat(angle1);
    Matrix4x4 M2 = getRotZMat(angle2);
    Matrix4x4 M3 = getRotXMat(a);
    Matrix4x4 invM2 = getInvRotZMat(angle2);
    Matrix4x4 invM1 = getInvRotYMat(angle1);

    Matrix4x4 rotMat = MT2 * invM1 * invM2 * M3 * M2 * M1 * MT1;
    return rotMat;
}


// @returns the inverse scale matrix described by the vector
Matrix4x4 getInvScaleMat(const Vector4 &v) {
    Matrix4x4 invScaleMat = Matrix4x4(1.0/v.x, 0, 0, 0,
                                       0, 1.0/v.y, 0 ,0,
                                       0, 0, 1.0/v.z, 0,
                                       0, 0, 0, 1);
    return invScaleMat;
}

// @returns the inverse translation matrix described by the vector
Matrix4x4 getInvTransMat(const Vector4 &v) {
    Matrix4x4 invTransMat = Matrix4x4(1, 0, 0, -v.x,
                                      0, 1, 0, -v.y,
                                      0, 0, 1, -v.z,
                                      0, 0, 0, 1);
    return invTransMat;
}

// @returns the inverse rotation matrix about the x axis by the specified angle
Matrix4x4 getInvRotXMat (const REAL radians) {
    REAL cosVal = cos(radians);
    REAL sinVal = sin(radians);
    Matrix4x4 invRotXMat = Matrix4x4(1, 0, 0, 0,
                                     0, cosVal, sinVal, 0,
                                     0, -sinVal, cosVal, 0,
                                     0, 0, 0, 1);
    return invRotXMat;
}

// @returns the inverse rotation matrix about the y axis by the specified angle
Matrix4x4 getInvRotYMat (const REAL radians) {
    REAL cosVal = cos(radians);
    REAL sinVal = sin(radians);
    Matrix4x4 invRotYMat = Matrix4x4(cosVal, 0, -sinVal, 0,
                            0, 1, 0, 0,
                            sinVal, 0, cosVal, 0,
                            0, 0, 0, 1);
    return invRotYMat;
}

// @returns the inverse rotation matrix about the z axis by the specified angle
Matrix4x4 getInvRotZMat (const REAL radians) {
    REAL cosVal = cos(radians);
    REAL sinVal = sin(radians);
    Matrix4x4 invRotZMat = Matrix4x4(cosVal, sinVal, 0, 0,
                                     -sinVal, cosVal, 0, 0,
                                     0, 0, 1, 0,
                                     0, 0, 0, 1);
    return invRotZMat;
}

// @returns the inverse rotation matrix around the vector and point by the specified angle
Matrix4x4 getInvRotMat  (const Vector4 &p, const Vector4 &v, const REAL a) {
   return getRotMat(p,v,-a);//trivially can get inverse just by using negative angle
}

//@}---------------------------------------------------------------------

