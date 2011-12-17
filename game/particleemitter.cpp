#include "particleemitter.h"

#include <iostream>
using namespace std;

ParticleEmitter::ParticleEmitter(OrbitCamera *cam, int num_particles, GLuint textureID, float rad)
{
    m_camera = cam;
    m_textureID = textureID;
    m_radius = rad;

    m_isAlive = true;
    m_numparticles = num_particles;
    m_particles = new Particle[num_particles]; //DELETE THIS?

    // init particles
    initParticles();
}

ParticleEmitter::~ParticleEmitter()
{
    delete m_particles;
}

void ParticleEmitter::initParticles()
{
    for (int i = 0; i < m_numparticles; i++) {
        Particle &p = m_particles[i];

        p.active = false;
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
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    for (int i = 0; i < m_numparticles; i++) {
        Particle &p = m_particles[i];
        if (p.lifetime <= 0 || !p.active)
            continue;

        // draw particles
        glColor4f(p.r, p.g, p.b, p.lifetime);

        // DO SOMETHING FOR PARTICLE RADIUSSSSSS##################

        float x = p.pos.x;
        float y = p.pos.y;
        float z = p.pos.z;
        drawParticle(x, y, z, m_radius);
       // glClearDepth(1.0);
    }

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void ParticleEmitter::drawParticle(float x, float y, float z, float r)
{
    r = r / 2;

    Vector3 w(-Vector3::fromAngles(m_camera->theta, m_camera->phi));
    Vector3 v = m_camera->up;
    Vector3 u = w.cross(v);

    u.normalize();
    v.normalize();

    Vector3 c(x, y, z);
    Vector3 c1 = c + r * u - r * v;
    Vector3 c2 = c + r * u + r * v;
    Vector3 c3 = c - r * u + r * v;
    c = c - r * u - r * v;

    glBegin(GL_QUADS);
    glTexCoord2d(0, 1);
    glVertex3fv(c.xyz);

    glTexCoord2d(0, 0);
    glVertex3fv(c1.xyz);

    glTexCoord2d(1, 0);
    glVertex3fv(c2.xyz);

    glTexCoord2d(1, 1);
    glVertex3fv(c3.xyz);
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
