#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "gameobject.h"
#include "resourceloader.h"
#include "game/particleemitter.h"

//! Projectile class: represents a projectile that is fired
class Projectile : public GameObject
{
public:
    Projectile(Model model, ParticleEmitter* em);
    virtual ~Projectile();

    void setEmitter(ParticleEmitter* em) { m_emitter = em;};
    ParticleEmitter *getEmitter() { return m_emitter; };
    void resetLifetime() {m_lifetime = 1;}
    void setIsAlive(bool status);

    void act();

private:
    float m_lifetime;
    ParticleEmitter *m_emitter;
};

#endif // PROJECTILE_H
