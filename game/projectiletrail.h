#ifndef PROJECTILETRAIL_H
#define PROJECTILETRAIL_H

#include "particleemitter.h"
#include "gameobject.h"

class ProjectileTrail : public ParticleEmitter
{
public:
    ProjectileTrail(Vector3 initPos);
    void updateParticles();
    void initParticles();

private:

};

#endif // PROJECTILETRAIL_H