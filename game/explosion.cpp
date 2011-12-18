#include "explosion.h"

Explosion::Explosion(OrbitCamera *cam, Vector3 initPos, GLuint textureID) : ParticleEmitter(cam, 500, textureID, 1.3)
{
    ParticleEmitter::setPosition(initPos);
    //initParticles();
}

void Explosion::initParticles()
{
    for (int i = 0; i < m_numparticles; i++) {
        Particle &p = m_particles[i];
        p.active = true;
        p.lifetime = 1.0;
        p.decay = (-1 * (rand() % 100 / 1000.f) - .0020);
        
        p.r = 1.0;
        p.g = .25;
        p.b = 0;
        p.pos = ParticleEmitter::getPosition();

        float rx = rand() % 5000 / 10000.f - .25;
        float ry = rand() % 5000 / 10000.f - .25;
        float rz = rand() % 5000 / 10000.f - .25;

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

        p.vel = .96 * p.vel;
        p.pos += p.vel;
        p.lifetime += p.decay;

        anyActive = true;
    }

    m_isAlive = anyActive;
}
