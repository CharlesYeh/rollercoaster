#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "sweepprune/BoundingBox.h"
#include <QtOpenGL>

class ParticleEmitter : public BoundingBox
{
public:
    struct Particle {
        float lifetime;
        float decay;
        float r, g, b;
        Vector3 pos;
        Vector3 vel;
    };

    ParticleEmitter();
    virtual void initParticle(Particle *p);
    virtual void updateParticles();
    virtual void drawParticles();
    virtual void drawParticle(float x, float y, float z, float r);

    static const int NUM_PARTICLES = 10;

private:
    GLuint m_texture;
    Particle *m_particles[NUM_PARTICLES];
};

#endif // PARTICLEEMITTER_H
