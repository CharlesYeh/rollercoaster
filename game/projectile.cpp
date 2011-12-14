#include "projectile.h"

Projectile::Projectile(Model model, ParticleEmitter *pe) : GameObject(model)
{
    m_emitter = pe;
}

Projectile::~Projectile()
{
}

void Projectile::act()
{
    GameObject::act();
    m_emitter->setPosition(getPosition());
}
