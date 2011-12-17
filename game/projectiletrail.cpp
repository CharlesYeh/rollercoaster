#include "projectiletrail.h"
#include <iostream>
using namespace std;

ProjectileTrail::ProjectileTrail(OrbitCamera *cam, Vector3 initPos, GLuint textureID) : ParticleEmitter(cam, 200, textureID)
{
    ParticleEmitter::setPosition(initPos);
    //initParticles();
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
            p.active = true;
            p.pos = ParticleEmitter::getPosition();
            p.lifetime = 1;
        }
    }
}

