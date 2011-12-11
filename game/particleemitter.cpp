#include "particleemitter.h"

ParticleEmitter::ParticleEmitter()
{
    // init particles
    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle *p = new Particle();

        p->lifetime = 1;
        p->decay = -.0001;
        p->r = p->g = p->b = .3;

        // reset pos and vel?
        p->pos = getPosition();

        m_particles[i] = p;
    }
}

void ParticleEmitter::drawParticles()
{
    //glBindTexture(GL_TEXTURE_2D, m_texture);

    glDisable(GL_CULL_FACE);
    glBegin(GL_QUADS);

    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle *p = m_particles[i];
        if (p->lifetime <= 0)
            continue;

        // draw particles
        glColor3f(p->r, p->g, p->b);

        // DO SOMETHING FOR PARTICLE RADIUSSSSSS##################
        float r = 10;

        float x = p->pos.x;
        float y = p->pos.y;
        float z = p->pos.z;

        glTexCoord2d(0, 0);
        glVertex3f(x - r, y - r, z);
        glTexCoord2d(1, 0);
        glVertex3f(x + r, y - r, z);
        glTexCoord2d(1, 1);
        glVertex3f(x + r, y + r, z);
        glTexCoord2d(0, 1);
        glVertex3f(x - r, y + r, z);
    }

    glEnable(GL_CULL_FACE);
}

void ParticleEmitter::updateParticles()
{
    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle *p = m_particles[i];
        p->pos += p->vel;
        p->lifetime += p->decay;

        if (p->lifetime <= 0) {
            // do something to dead particle
        }
    }
}
