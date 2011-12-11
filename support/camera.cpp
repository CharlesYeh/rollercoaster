#include "camera.h"
#include <qgl.h>
#include <stdio.h>
#include <stdlib.h>

void OrbitCamera::mouseMove(const Vector2 &delta)
{
    // Rotate the eye vector around the origin
    theta += delta.x * 0.01f;
    phi += delta.y * 0.01f;

    // Keep theta in [0, 2pi] and phi in [-pi/2, pi/2]
    theta -= floorf(theta / M_2PI) * M_2PI;
    phi = max(0.01f - M_PI / 2, min(M_PI / 2 - 0.01f, phi));
}

void OrbitCamera::mouseWheel(float delta)
{
    zoom *= powf(0.999f, delta);
}

void OrbitCamera::jitterCamera() {
    //mildly perturbs the camera's position
    float randX, randY, randZ;
    randX = (rand() % 100 - 50) / 5000.0;
    randY = (rand() % 100 - 50) / 5000.0;
    randZ = (rand() % 100 - 50) / 5000.0;
    center.x += randX;
    center.y += randY;
    center.z += randZ;

}
