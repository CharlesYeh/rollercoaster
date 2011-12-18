#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <QThread>
#include <vector>
#include "gameobject.h"
#include "projectile.h"
#include "beziercurve.h"
#include "camera.h"
#include "particleemitter.h"
#include "projectiletrail.h"
#include "explosion.h"
#include <string>
#include <set>

#include <QMutex>
#include"SweepPruner.h"

//! GameEngine class. Holds the main loop for game logic plus does most of the work.

//structure for holding game objects as they travel along bezier curves
struct CurveMount
{
    GameObject *gameObj;
    BezierCurve *curve;
    float t;
    float tChange;
};

class GameEngine : public QThread
{
public:
    static const float FRAME_RATE   = 1  / 40.f;
    static const int MAX_SHAKES     = 600;
    static const int NUM_ROCKETS    = 15;
    static const int NUM_EXPLOSIONS = 20;
    static const int NUM_ENEMIES    = 70;
    static const float PROJECTILE_SPEED = .03;

    explicit GameEngine(QObject *parent = 0);
    virtual ~GameEngine();

    void start();
    void run();
    void spawnProjectile(Vector3 dir);
    void setCamera(OrbitCamera* cam) { m_camera = cam; }
    void fireProjectile(Vector3 dir);

    std::vector<GameObject*> *getGameObjects() { return m_gobjects; };
    std::vector<ParticleEmitter*> *getEmitters() { return m_emitters; };
    std::set<CollisionPair> *getCollisions() { return m_collisions; };
    std::map<std::string, Model> *getModels() { return m_models; };

    int getHits() { return m_hits; };
    int getFired() { return m_fired; };

    void toggleRotation() { m_turnCamera = !m_turnCamera; };
    void togglePause() { m_hitpause = !m_hitpause; };

    void stop();
    bool running();
    QMutex mutex;

private:
    void spawnCurveEnemies(int numEnemies); //! Randomly generates enemies that move along curves
    BezierCurve* generateCurve(int numPoints, int sizeCurve); //! Randomly generates curves

    std::vector<Explosion*> *m_explosions;
    std::vector<Projectile*> *m_projectiles;
    std::vector<GameObject*> *m_gobjects;
    std::vector<ParticleEmitter*> *m_emitters;
    std::vector<CurveMount> *m_curveMounts;
    std::map<std::string, Model> *m_models; //map of models, mapped by filename

    // score
    int m_hits, m_fired;
    bool m_turnCamera, m_hitpause;

    // textures and models
    GLuint m_textTrail, m_textExplosion;
    std::string ROCKET_MODEL, SHIP_MODEL, UFO_MODEL;

    // projectile variables
    bool m_canFire;
    Vector3 m_projectileDir;

    // collision detection
    std::set<CollisionPair> *m_collisions;
    SweepPruner *m_pruner;


    float m_refractPeriod;
    bool m_stop;
    bool m_running;

    bool m_shake; //alert to shake camera
    int m_curNumShakes;

    BezierCurve *m_curve;
    OrbitCamera *m_camera;
    CurveMount m_cameraMount;
};

#endif // GAMEENGINE_H
