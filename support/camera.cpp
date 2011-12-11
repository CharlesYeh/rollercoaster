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

void OrbitCamera::jitterCamera(float perturb) {
    //mildly perturbs the camera's position
    float randX, randY, randZ;
    randX = (rand() % 200 - 100) / perturb;
    randY = (rand() % 200 - 100) / perturb;
    randZ = (rand() % 200 - 100) / perturb;
    center.x += randX;
    center.y += randY;
    center.z += randZ;

}
