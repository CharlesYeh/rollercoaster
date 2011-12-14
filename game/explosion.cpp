#include "explosion.h"

Explosion::Explosion() : ParticleEmitter()
{
}

void Explosion::initParticle(Particle &p)
{
    p.pos = getPosition();

    float rx = rand() % 1000 / 10000.f - 5000;
    float ry = rand() % 1000 / 10000.f - 5000;
    float rz = rand() % 1000 / 10000.f - 5000;

    p.vel = Vector3(rx, ry, rz);
}

void Explosion::drawParticle(float x, float y, float z, float r)
{
    // bind texture
    ParticleEmitter::drawParticle(x, y, z, r);
    // unbind texture
}
