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
Matrix4x4 getScaleMat(const Vector4 &v) {
    REAL arrS[16] = {v.x, 0, 0, 0,
                     0, v.y, 0, 0,
                     0, 0, v.z, 0,
                     0, 0, 0, 1};

    return Matrix4x4(arrS);
}

// @returns the translation matrix described by the vector
Matrix4x4 getTransMat(const Vector4 &v) {

    REAL arrT[16] = {1, 0, 0, v.x,
                     0, 1, 0, v.y,
                     0, 0, 1, v.z,
                     0, 0, 0, 1};

    return Matrix4x4(arrT);

}

// @returns the rotation matrix about the x axis by the specified angle
Matrix4x4 getRotXMat(const REAL radians) {

    REAL arrR[16] = {1, 0,            0,             0,
                     0, cos(radians), -sin(radians), 0,
                     0, sin(radians), cos(radians),  0,
                     0, 0,            0,             1};

    return Matrix4x4(arrR);

}

// @returns the rotation matrix about the y axis by the specified angle
Matrix4x4 getRotYMat (const REAL radians) {

    REAL arrR[16] = {cos(radians), 0, sin(radians), 0,
                     0, 1, 0, 0,
                     -sin(radians), 0, cos(radians), 0,
                     0, 0, 0, 1};

    return Matrix4x4(arrR);

}

// @returns the rotation matrix about the z axis by the specified angle
Matrix4x4 getRotZMat (const REAL radians) {

    REAL arrR[16] = {cos(radians), -sin(radians), 0, 0,
                     sin(radians), cos(radians),  0, 0,
                     0,            0,             1, 0,
                     0,            0,             0, 1};

    return Matrix4x4(arrR);

}

// @returns the rotation matrix around the vector and point by the specified angle
Matrix4x4 getRotMat  (const Vector4 &p, const Vector4 &v, const REAL a) {

    float rz = atan2(v.z, v.x);
    float ry = -atan2(v.y, sqrt(v.x * v.x + v.z * v.z));

    return getTransMat(p) * getInvRotYMat(rz) * getInvRotZMat(ry) * getRotXMat(a) *
            getRotZMat(ry) * getRotYMat(rz) * getInvTransMat(p);
}


// @returns the inverse scale matrix described by the vector
Matrix4x4 getInvScaleMat(const Vector4 &v) {

    REAL arrS[16] = {1 / v.x, 0, 0, 0,
                     0, 1 / v.y, 0, 0,
                     0, 0, 1 / v.z, 0,
                     0, 0, 0, 1};

    return Matrix4x4(arrS);

}

// @returns the inverse translation matrix described by the vector
Matrix4x4 getInvTransMat(const Vector4 &v) {

    REAL arrT[16] = {1, 0, 0, -v.x,
                     0, 1, 0, -v.y,
                     0, 0, 1, -v.z,
                     0, 0, 0, 1};

    return Matrix4x4(arrT);

}

// @returns the inverse rotation matrix about the x axis by the specified angle
Matrix4x4 getInvRotXMat (const REAL radians) {

    REAL arrR[16] = {1, 0,            0,             0,
                     0, cos(radians), sin(radians), 0,
                     0, -sin(radians), cos(radians),  0,
                     0, 0,            0,             1};

    return Matrix4x4(arrR);

}

// @returns the inverse rotation matrix about the y axis by the specified angle
Matrix4x4 getInvRotYMat (const REAL radians) {

    REAL arrR[16] = {cos(radians), 0, -sin(radians), 0,
                     0, 1, 0, 0,
                     sin(radians), 0, cos(radians), 0,
                     0, 0, 0, 1};

    return Matrix4x4(arrR);

}

// @returns the inverse rotation matrix about the z axis by the specified angle
Matrix4x4 getInvRotZMat (const REAL radians) {

    REAL arrR[16] = {cos(radians), sin(radians), 0, 0,
                     -sin(radians), cos(radians),  0, 0,
                     0,            0,             1, 0,
                     0,            0,             0, 1};

    return Matrix4x4(arrR);

}

// @returns the inverse rotation matrix around the vector and point by the specified angle
Matrix4x4 getInvRotMat  (const Vector4 &p, const Vector4 &v, const REAL a) {

    float rz = atan2(v.z, v.x);
    float ry = -atan2(v.y, sqrt(v.x * v.x + v.z * v.z));

    return getTransMat(p) * getInvRotYMat(rz) * getInvRotZMat(ry) * getInvRotXMat(a) *
            getRotZMat(ry) * getRotYMat(rz) * getInvTransMat(p);
}


//@}---------------------------------------------------------------------

