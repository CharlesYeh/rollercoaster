#include "explosion.h"

Explosion::Explosion(Vector3 initPos, GLuint textureID) : ParticleEmitter(200, textureID)
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
        p.decay = -1 * (rand() % 100 / 500.f);
        //p.r = p.g = p.b = .3;
        p.r = 1.0;
        p.g = p.b = 0;
        p.pos = ParticleEmitter::getPosition();

        float rx = rand() % 1000 / 10000.f - .05;
        float ry = rand() % 1000 / 10000.f - .05;
        float rz = rand() % 1000 / 10000.f - .05;

        p.vel = Vector3(rx, ry, rz);
        std::cout << p.vel << std::endl;
        //p.vel = Vector3();
    }
}

void Explosion::updateParticles()
{
    for (int i = 0; i < m_numparticles; i++) {
        Particle &p = m_particles[i];
        p.pos += p.vel;
        p.lifetime += p.decay;

        if (p.lifetime <= 0) {
            p.active = false;
        }
    }
}
