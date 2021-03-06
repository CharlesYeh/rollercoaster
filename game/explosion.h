#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "particleemitter.h"

//! Explosion class: represents an explosion for when a projectile collides with a game object
class Explosion : public ParticleEmitter
{
public:
    Explosion(OrbitCamera *cam, Vector3 initPos, GLuint textureID);

    void updateParticles();
    void initParticles();
};

#endif // EXPLOSION_H
