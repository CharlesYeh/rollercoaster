#include "projectiletrail.h"
#include <iostream>
using namespace std;

ProjectileTrail::ProjectileTrail(OrbitCamera *cam, Vector3 initPos, GLuint textureID) : ParticleEmitter(cam, 200, textureID, .3)
{
    ParticleEmitter::setPosition(initPos);
}

void ProjectileTrail::initParticles()
{
    for (int i = 0; i < m_numparticles; i++) {
        Particle &p = m_particles[i];
        p.active = false;
        p.lifetime = rand() % 1000 / 1000.f;
        p.decay = - (rand() % 10000) / 10000.f / 100.f - .02;

        p.r = p.g = p.b = 1;
        p.pos = getPosition();
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
            p.active = true;
            p.pos = ParticleEmitter::getPosition();
            p.lifetime = 1;
        }
    }
}

