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
#include <string>

struct CurveMount
{
    GameObject *gameObj;
    BezierCurve *curve;
    float t;
};

class GameEngine : public QThread
{
public:
    static const int   MAX_SHAKES = 50000;
    static const float FRAME_RATE = 1  / 40.f;

    explicit GameEngine(QObject *parent = 0);
    virtual ~GameEngine();

    void start();
    void run();
    void spawnProjectile(Vector3 dir);
    void setCamera(OrbitCamera* cam) {m_camera = cam;}
    void setCanFire() {m_canFire = true;}

    std::vector<GameObject*> *getGameObjects() { return m_gobjects; };
    std::vector<ParticleEmitter*> *getEmitters() { return m_emitters; };

    void stop();
    bool running();

private:
    bool m_stop;
    bool m_running;
    std::string ROCKET_MODEL;

    bool m_shake; //alert to shake camera
    int m_curNumShakes;
    bool m_canFire;

    BezierCurve *m_curve;
    OrbitCamera *m_camera;

    std::vector<GameObject*> *m_gobjects;
    std::vector<ParticleEmitter*> *m_emitters;
    std::vector<CurveMount> *m_curveMounts;
    std::map<std::string, Model> m_models; //map of models, mapped by filename
};

#endif // GAMEENGINE_H
