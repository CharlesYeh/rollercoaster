#include "particleemitter.h"

#include <iostream>
using namespace std;

ParticleEmitter::ParticleEmitter(int num_particles)
{
    m_isAlive = true;
    m_numparticles = num_particles;
    m_particles = new Particle[num_particles]; //DELETE THIS?

    // init particles
  initParticles();
}

void ParticleEmitter::initParticles()
{
    for (int i = 0; i < m_numparticles; i++) {
        Particle &p = m_particles[i];
        p.lifetime = 1.0;
        p.decay = -.00001;
        p.r = p.g = p.b = .3;
        p.pos = getPosition();
        float rx = rand() % 1000 / 1000000.f - .0005;
        float ry = rand() % 1000 / 1000000.f - .0005;
        float rz = rand() % 1000 / 1000000.f - .0005;

        p.vel = Vector3(rx, ry, rz);
    }
}

void ParticleEmitter::drawParticles()
{
    //glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);

    glPushMatrix();
    GLfloat matrix[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    matrix[0] = 1.0;
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;
    matrix[4] = 0.0;
    matrix[5] = 1.0;
    matrix[6] = 0.0;
    matrix[7] = 0.0;
    glLoadMatrixf(matrix);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    for (int i = 0; i < m_numparticles; i++) {
        Particle &p = m_particles[i];
        if (p.lifetime <= 0)
            continue;
        // draw particles
        //glColor3f(p->r, p->g, p->b);

        // DO SOMETHING FOR PARTICLE RADIUSSSSSS##################

        float x = p.pos.x;
        float y = p.pos.y;
        float z = p.pos.z;
        drawParticle(x, y, z, .1);
    }

    //glAccum for particle trails
    glDisable(GL_BLEND);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE);

    /*glAccum(GL_MULT, 0.8);
    glAccum(GL_ACCUM, .2);
    glAccum(GL_RETURN, 1);*/

}

void ParticleEmitter::drawParticle(float x, float y, float z, float r)
{
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glTexCoord2d(0, 1);
    glVertex3f(x - r, y + r, z);
    glTexCoord2d(0, 0);
    glVertex3f(x - r, y - r, z);
    glTexCoord2d(1, 0);
    glVertex3f(x + r, y - r, z);
    glTexCoord2d(1, 1);
    glVertex3f(x + r, y + r, z);
    glEnd();
}

void ParticleEmitter::updateParticles()
{
    for (int i = 0; i < m_numparticles; i++) {
        Particle &p = m_particles[i];
        p.pos += p.vel;
        //cout << p->pos << endl;
        p.lifetime += p.decay;

        if (p.lifetime <= 0) {
            // do something to dead particle
        }
    }
}
