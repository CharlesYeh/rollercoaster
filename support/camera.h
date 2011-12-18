#ifndef CAMERA_H
#define CAMERA_H

#include <QMouseEvent>
#include "vector.h"

/**
    An orbiting perspective camera specified by a center, two angles, and a zoom factor

    @author: Justin Ardini (jardini)
**/
struct OrbitCamera
{
    const static int JITTER_MAGNITUDE = 6;

    Vector3 center, up;
    Vector3 jitter;

    float theta, phi;
    float fovy;
    float zoom;

    void setPosition(Vector3 v);

    void mouseMove(const Vector2 &delta);
    void mouseWheel(float delta);
    void jitterCamera(float magnifier);
};

#endif // CAMERA_H
