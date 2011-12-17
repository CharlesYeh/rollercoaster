#include "projectile.h"

Projectile::Projectile(Model model) : GameObject(model)
{
    //m_emitter = pe;
    m_lifetime = 1.0;

}

Projectile::~Projectile()
{
}

void Projectile::act()
{
    m_lifetime -= 0.00001;
    if (m_lifetime < 0) {
       m_isAlive = false;
       m_emitter->setIsAlive(false);
    }

    GameObject::act();

    Vector3 offsetted = getPosition();
    m_emitter->setPosition(offsetted);
}
