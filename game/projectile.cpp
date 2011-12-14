#include "projectile.h"

Projectile::~Projectile() {
    delete m_emitter;
}

ParticleEmitter* Projectile::getEmitter() {
    return m_emitter;
}
