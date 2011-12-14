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

    ParticleEmitter(int num_particles = 300);

    virtual void initParticles();
    virtual void updateParticles();
    virtual void drawParticles();
    virtual void drawParticle(float x, float y, float z, float r);

protected:
    int m_numparticles;
    int m_type;

    GLuint m_texture;
    Particle *m_particles;
};

#endif // PARTICLEEMITTER_H
