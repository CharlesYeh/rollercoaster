#ifndef PROJECTILETRAIL_H
#define PROJECTILETRAIL_H

#include "particleemitter.h"
#include "gameobject.h"

class ProjectileTrail : public ParticleEmitter
{
public:
    ProjectileTrail(OrbitCamera *cam, Vector3 initPos, GLuint textureID);
    void updateParticles();
    void initParticles();

private:

};

#endif // PROJECTILETRAIL_H
