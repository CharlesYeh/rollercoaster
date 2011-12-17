#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameobject.h"
#include "resourceloader.h"
#include "game/particleemitter.h"

class Projectile : public GameObject
{
public:
    Projectile(Model model, ParticleEmitter* em);
    virtual ~Projectile();

    void setEmitter(ParticleEmitter* em) { m_emitter = em;};
    ParticleEmitter *getEmitter() { return m_emitter; };
    void resetLifetime() {m_lifetime = 1;}

    void act();

private:
    float m_lifetime;
    ParticleEmitter *m_emitter;
};

#endif // PROJECTILE_H
