#include "projectiletrail.h"

ProjectileTrail::ProjectileTrail(Vector3 initPos) : ParticleEmitter(100)
{
    ParticleEmitter::setPosition(initPos);
    initParticles();
}

void ProjectileTrail::initParticles()
{
    for (int i = 0; i < m_numparticles; i++) {
        Particle &p = m_particles[i];
        p.lifetime = rand() % 100 / 200.f;
        p.decay = -.00001;
        p.r = p.g = p.b = .3;
        p.pos = ParticleEmitter::getPosition();

        float rx = rand() % 1000 / 10000000.f - .00005;
        float ry = rand() % 1000 / 10000000.f - .00005;
        float rz = rand() % 1000 / 10000000.f - .00005;

        p.vel = Vector3(rx, ry, rz);
    }
}

void ProjectileTrail::updateParticles()
{
    for (int i = 0; i < m_numparticles; i++) {
        Particle &p = m_particles[i];
        p.pos += p.vel;
        p.lifetime += p.decay;

        if (p.lifetime <= 0) {
            p.pos = ParticleEmitter::getPosition();
            p.lifetime = rand() % 100 / 100.f;
        }
    }
}
