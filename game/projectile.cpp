#include "projectile.h"

Projectile::Projectile(Model model, ParticleEmitter* pe) : GameObject(model)
{
    m_emitter = pe;
    m_lifetime = 1.0;
}

Projectile::~Projectile()
{
}

void Projectile::act()
{
    m_lifetime -= 0.01;
    GameObject::act();
    m_emitter->setPosition(getPosition());
}
