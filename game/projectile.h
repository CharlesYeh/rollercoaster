#ifndef PROJECTILE_H
#define PROJECTILE_H
\
#include "gameobject.h"
#include "resourceloader.h"
#include "particleemitter.h"

class Projectile : public GameObject
{
public:
    Projectile(Model model) : GameObject(model) {
        m_emitter = new ParticleEmitter();
    }

    virtual ~Projectile();

    ParticleEmitter* getEmitter();

private:
    ParticleEmitter *m_emitter;

};

#endif // PROJECTILE_H
