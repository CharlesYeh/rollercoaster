#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameobject.h"
#include "resourceloader.h"
#include "game/particleemitter.h"

class Projectile : public GameObject
{
public:
    Projectile(Model model, ParticleEmitter *pe);
    virtual ~Projectile();

    ParticleEmitter *getEmitter() { return m_emitter; };

    void act();

private:
    ParticleEmitter *m_emitter;

};

#endif // PROJECTILE_H
