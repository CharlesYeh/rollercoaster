#include "gameengine.h"

using namespace std;
GameEngine::GameEngine(QObject *parent)
{
    m_gobjects = new vector<GameObject*>();
    m_curveMounts = new vector<CurveMount>();
    m_camera = NULL;
}

GameEngine::~GameEngine()
{
    vector<GameObject*>::iterator iter;
    for (iter = m_gobjects->begin(); iter != m_gobjects->end(); iter++)
    {
        delete *iter;
    }

    delete m_gobjects;
    delete m_curveMounts;

    delete m_camera;
}

void GameEngine::start()
{
    GameObject *obj = new GameObject("models/xyzrgb_dragon.obj");
    m_gobjects->push_back(obj);
    GameObject *obj2 = new GameObject("models/xyzrgb_dragon.obj");
    obj->getPosition().y -= 1;
    m_gobjects->push_back(obj2);

    // create main track
    m_curve = new BezierCurve();
    m_curve->addPoint(-2, -1, 0);
    m_curve->addPoint(-1, 0, 0);
    m_curve->addPoint(0, 1, 0);
    m_curve->addPoint(1, 2, 0);

    CurveMount cameraMount;
    cameraMount.curve = m_curve;
    cameraMount.gameObj = NULL;
    cameraMount.t = 0;
    m_curveMounts->push_back(cameraMount);

    CurveMount mount;
    mount.curve = m_curve;
    mount.gameObj = obj;
    mount.t = 0;

    m_curveMounts->push_back(mount);

    QThread::start();
}

void GameEngine::run()
{
    while (true)
    {
        //--------------------act--------------------
        vector<GameObject*>::iterator iter;
        for (iter = m_gobjects->begin(); iter != m_gobjects->end(); iter++)
        {
            (*iter)->act();
        }

        //-------------------mounts-------------------
        vector<CurveMount>::iterator iter2;
        for (iter2 = m_curveMounts->begin(); iter2 != m_curveMounts->end(); iter2++)
        {
            CurveMount &m = *iter2;
            m.t += .000001;

            //first item in m_curveMounts is for the camera.
            if (iter2 == m_curveMounts->begin()) {
               m_camera->center = m_curve->quadraticSample(m.t);
            } else {
               m.gameObj->setPosition(m.curve->quadraticSample(m.t));
            }

        }

        sleep(FRAME_RATE);
    }
}

