#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <QThread>
#include <vector>
#include "gameobject.h"
#include "beziercurve.h"
#include "camera.h"
#include "particleemitter.h"

struct CurveMount
{
    GameObject *gameObj;
    BezierCurve *curve;
    float t;
};

class GameEngine : public QThread
{
public:
    static const float FRAME_RATE = 1 / 40.f;

    explicit GameEngine(QObject *parent = 0);
    virtual ~GameEngine();

    void start();
    void run();
    void spawnProjectile(Vector3 dir);
    void setCamera(OrbitCamera* cam) {m_camera = cam;}
    void setCanFire() {m_canFire = true;}

    std::vector<GameObject*> *getGameObjects() { return m_gobjects; };

private:
    bool m_canFire;

    ParticleEmitter *m_emitter;

    BezierCurve *m_curve;
    OrbitCamera *m_camera;

    std::vector<GameObject*> *m_gobjects;
    std::vector<CurveMount> *m_curveMounts;
    std::map<std::string, Model> m_models; //map of models, mapped by filename
};

#endif // GAMEENGINE_H
