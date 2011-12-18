#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "sweepprune/BoundingBox.h"
#include <QtOpenGL>
#include "support/camera.h"

//! ParticleEmitter for particle effects. Used for drawing and updating particles for explosions/projectile trails
class ParticleEmitter : public BoundingBox
{
public:
    struct Particle {
        bool active;
        float lifetime;     // lifetime normalized to [0, 1]
        float decay;
        float r, g, b;
        Vector3 pos;
        Vector3 vel;
    };

    ParticleEmitter(OrbitCamera *cam, int num_particles = 300, GLuint textureID = 0, float rad = .1);
    virtual ~ParticleEmitter();

    virtual void initParticles();
    virtual void updateParticles();
    virtual void drawParticles();
    virtual void drawParticle(float x, float y, float z, float r);

    bool getIsAlive() { return m_isAlive; }
    void setIsAlive(bool status) { m_isAlive = status;}

    void setCamera(OrbitCamera *cam) { m_camera = cam; };

protected:
    GLuint m_textureID;

    float m_lifetime;
    bool m_isAlive;
    int m_numparticles;
    int m_type;
    float m_radius;

    Particle *m_particles;

    OrbitCamera *m_camera;
};

#endif // PARTICLEEMITTER_H
