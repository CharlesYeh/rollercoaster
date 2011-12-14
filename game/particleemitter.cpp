#include "particleemitter.h"

#include <iostream>
using namespace std;

ParticleEmitter::ParticleEmitter()
{
    // init particles
    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle *p = new Particle();

        p->lifetime = 1000.0;
        p->decay = -.0001;
        p->r = p->g = p->b = .3;
        //p->vel = Vector3(0.00001,0,0);

        // reset pos and vel?
        p->pos = getPosition();
        p->vel = Vector3(rand() % 1000 / 1000000.f, rand() % 1000 / 1000000.f, rand() % 1000 / 1000000.f);

        m_particles[i] = p;
    }
}

void ParticleEmitter::drawParticles()
{
    //glBindTexture(GL_TEXTURE_2D, m_texture);

    //glDisable(GL_CULL_FACE);
    //glEnable(GL_BLEND);
    //glEnable(GL_TEXTURE_2D);


    //cout << m_particles[0]->pos << endl;

    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle *p = m_particles[i];
        if (p->lifetime <= 0)
            continue;

        //cout << "HI" << endl;

        // draw particles
        //glColor3f(p->r, p->g, p->b);

        // DO SOMETHING FOR PARTICLE RADIUSSSSSS##################
        float r = 0.2;

        float x = p->pos.x;
        float y = p->pos.y;
        float z = p->pos.z;

        glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glTexCoord2d(0, 0);
        glVertex3f(x - r, y - r, z);
        glTexCoord2d(0, 1);
        glVertex3f(x - r, y + r, z);
        glTexCoord2d(1, 0);
        glVertex3f(x + r, y - r, z);
        glTexCoord2d(1, 1);
        glVertex3f(x + r, y + r, z);
        glTexCoord2d(0, 0);
        glVertex3f(x - r, y - r, z);
        glEnd();
    }

    //glEnable(GL_CULL_FACE);
}

void ParticleEmitter::updateParticles()
{
    for (int i = 0; i < NUM_PARTICLES; i++) {
        Particle *p = m_particles[i];
        cout << p->vel << endl;
        p->pos += p->vel;
        p->lifetime += p->decay;

        if (p->lifetime <= 0) {
            // do something to dead particle
        }
    }
}
