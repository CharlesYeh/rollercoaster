#ifndef PROJECTILETRAIL_H
#define PROJECTILETRAIL_H

#include "particleemitter.h"
#include "gameobject.h"

class ProjectileTrail : public ParticleEmitter
{
public:
    ProjectileTrail(GameObject* objectTrailing);
    void updateParticles();
    void initParticles();

private:
        GameObject* m_object;

};

#endif // PROJECTILETRAIL_H
