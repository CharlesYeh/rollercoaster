#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <QThread>
#include <vector>
#include "gameobject.h"
#include "beziercurve.h"

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

    std::vector<GameObject*> *getGameObjects() { return m_gobjects; };

private:
    BezierCurve *m_curve;

    std::vector<GameObject*> *m_gobjects;
    std::vector<CurveMount> *m_curveMounts;
};

#endif // GAMEENGINE_H
