#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "particleemitter.h"

class Explosion : public ParticleEmitter
{
public:
    Explosion(GLuint textureID);

    void initParticle(Particle &p);
    void drawParticle(float x, float y, float z, float r);
};

#endif // EXPLOSION_H
