#include "projectile.h"

Projectile::Projectile(Model model, ParticleEmitter* pe) : GameObject(model)
{
    m_emitter = pe;
    m_lifetime = 1.0;

}

Projectile::~Projectile()
{
}

void Projectile::setIsAlive(bool status) {
    m_isAlive = status;
    if (!m_isAlive)
        m_emitter->setIsAlive(status);
}

void Projectile::act()
{
    m_lifetime -= 0.0001;
    if (m_lifetime < 0) {
        setIsAlive(false);
    }

    GameObject::act();

    Vector3 offsetted = getPosition();
    m_emitter->setPosition(offsetted);
}
