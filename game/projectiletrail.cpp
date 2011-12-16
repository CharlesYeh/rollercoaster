#include "projectiletrail.h"

ProjectileTrail::ProjectileTrail(Vector3 initPos, GLuint textureID) : ParticleEmitter(100, textureID)
{
    ParticleEmitter::setPosition(initPos);
    initParticles();
}

void ProjectileTrail::initParticles()
{
    for (int i = 0; i < m_numparticles; i++) {
        Particle &p = m_particles[i];
        p.lifetime = rand() % 100 / 400000.f;
        p.decay = -.000005;
        p.r = p.g = p.b = .3;
        p.pos = ParticleEmitter::getPosition();

        /*float rx = rand() % 1000 / 10000.f - .05;
        float ry = rand() % 1000 / 10000.f - .05;
        float rz = rand() % 1000 / 10000.f - .05;

        p.vel = Vector3(rx, ry, rz);*/
        p.vel = Vector3();
    }
}

void ProjectileTrail::updateParticles()
{
    for (int i = 0; i < m_numparticles; i++) {
        Particle &p = m_particles[i];
        //p.pos += p.vel;
        p.lifetime += p.decay;

        if (p.lifetime <= 0) {
            p.pos = ParticleEmitter::getPosition();
            p.lifetime = rand() % 100 / 400000.f;
        }
    }
}

