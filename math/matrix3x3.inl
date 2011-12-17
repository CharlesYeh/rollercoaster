#include "matrix3x3.h"

// @returns the rotation matrix about the x axis by the specified angle
Matrix3x3 getRotXMat(const REAL radians) {

    REAL arrR[9] = {1, 0,            0,
                     0, cos(radians), -sin(radians),
                     0, sin(radians), cos(radians)};

    return Matrix3x3(arrR);

}

// @returns the rotation matrix about the y axis by the specified angle
Matrix3x3 getRotYMat (const REAL radians) {

    REAL arrR[9] = {cos(radians),  0, sin(radians),
                    0, 1, 0,
                    -sin(radians), 0, cos(radians)};

    return Matrix3x3(arrR);
}

Matrix3x3 getInvRotYMat (const REAL radians) {

    REAL arrR[9] = {cos(-radians),  0, sin(-radians),
                    0, 1, 0,
                    -sin(-radians), 0, cos(-radians)};

    return Matrix3x3(arrR);
}

// @returns the rotation matrix about the z axis by the specified angle
Matrix3x3 getRotZMat (const REAL radians) {

    REAL arrR[9] = {cos(radians), -sin(radians), 0,
                    sin(radians), cos(radians),  0,
                    0,            0,             1};

    return Matrix3x3(arrR);

}

Matrix3x3 getInvRotZMat (const REAL radians) {

    REAL arrR[9] = {cos(-radians), -sin(-radians), 0,
                    sin(-radians), cos(-radians),  0,
                    0,            0,             1};

    return Matrix3x3(arrR);

}

// @returns the rotation matrix around the vector and point by the specified angle
Matrix3x3 getRotMat  (const Vector3 &v, const REAL a) {

    float rz = atan2(v.z, v.x);
    float ry = -atan2(v.y, sqrt(v.x * v.x + v.z * v.z));

    return getInvRotYMat(rz) * getInvRotZMat(ry) * getRotXMat(a) *
            getRotZMat(ry) * getRotYMat(rz);
}
