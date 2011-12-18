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
    static const float FRAME_RATE = 1  / 40.f;
    static const int MAX_SHAKES = 800;
    static const int NUM_ROCKETS = 15;
    static const int NUM_EXPLOSIONS = 20;
    static const float PROJECTILE_SPEED = .02;

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

    void stop();
    bool running();
    QMutex mutex;

private:
    void spawnCurveEnemies(int numEnemies);
    BezierCurve* generateCurve(int numPoints, int sizeCurve);

    // textures
    GLuint m_textTrail, m_textExplosion;

    bool m_canFire;
    Vector3 m_projectileDir;

    std::set<CollisionPair> *m_collisions;
    SweepPruner *m_pruner;

    float m_refractPeriod;
    bool m_stop;
    bool m_running;
    std::string ROCKET_MODEL, SHIP_MODEL, UFO_MODEL;

    bool m_shake; //alert to shake camera
    int m_curNumShakes;

    BezierCurve *m_curve;
    OrbitCamera *m_camera;
    CurveMount m_cameraMount;


    std::vector<Explosion*> *m_explosions;
    std::vector<Projectile*> *m_projectiles;
    std::vector<GameObject*> *m_gobjects;
    std::vector<ParticleEmitter*> *m_emitters;
    std::vector<CurveMount> *m_curveMounts;
    std::map<std::string, Model> *m_models; //map of models, mapped by filename
};

#endif // GAMEENGINE_H
