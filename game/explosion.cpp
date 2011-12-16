#include "explosion.h"

Explosion::Explosion(OrbitCamera *cam, Vector3 initPos, GLuint textureID) : ParticleEmitter(cam, 200, textureID, .8)
{
    ParticleEmitter::setPosition(initPos);
    initParticles();
}

void Explosion::initParticles()
{
    for (int i = 0; i < m_numparticles; i++) {
        Particle &p = m_particles[i];
        p.active = true;
        //p.lifetime = rand() % 100 / 400000.f;
        p.lifetime = 1.0;
        p.decay = -1 * (rand() % 100 / 500.f) - .01;
        //p.r = p.g = p.b = .3;
        
        p.r = 1.0;
        p.g = .2;
        p.b = 0;
        p.pos = ParticleEmitter::getPosition();

        float rx = rand() % 3000 / 10000.f - .15;
        float ry = rand() % 3000 / 10000.f - .15;
        float rz = rand() % 3000 / 10000.f - .15;

        p.vel = Vector3(rx, ry, rz);
    }
}

void Explosion::updateParticles()
{
    bool anyActive = false;

    for (int i = 0; i < m_numparticles; i++) {
        Particle &p = m_particles[i];

        if (p.lifetime <= 0) {
            p.active = false;
            continue;
        }

        p.vel = .9 * p.vel;
        p.pos += p.vel;
        p.lifetime += p.decay;

        anyActive = true;
    }

    m_isAlive = anyActive;
}
