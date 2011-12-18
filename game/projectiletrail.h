#ifndef PROJECTILETRAIL_H
#define PROJECTILETRAIL_H

#include "particleemitter.h"
#include "gameobject.h"

//! ProjectileTrail class: Particle emitter for trails of projectiles fired.
class ProjectileTrail : public ParticleEmitter
{
public:
    ProjectileTrail(OrbitCamera *cam, Vector3 initPos, GLuint textureID);
    void updateParticles();
    void initParticles();
    void setIsAlive(bool status) { m_isAlive = status;}

private:

};

#endif // PROJECTILETRAIL_H
