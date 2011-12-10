#include "gameengine.h"

using namespace std;
GameEngine::GameEngine(QObject *parent)
{
    m_gobjects = new vector<GameObject*>();
    m_curveMounts = new vector<CurveMount>();
    m_camera = NULL;

    string objModel = "models/xyzrgb_dragon.obj";
    m_models.insert(pair<std::string,Model>(objModel, ResourceLoader::loadObjModel(objModel.c_str())));

    objModel = "models/sphere.obj";
    m_models.insert(pair<std::string,Model>(objModel, ResourceLoader::loadObjModel(objModel.c_str())));
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

    //NOTE: NOT DELETING M_CAMERA BECAUSE OWNED BY GLWIDGET
}

void GameEngine::start()
{

    //GameObject *obj = new GameObject("models/xyzrgb_dragon.obj");
    GameObject *obj = new GameObject(m_models["models/xyzrgb_dragon.obj"]);
    obj->getPosition().y -= 1;
    m_gobjects->push_back(obj);

    GameObject *obj2 = new GameObject(m_models["models/xyzrgb_dragon.obj"]);
    obj2->setVelocity(Vector3(.0000002, 0, 0));
    m_gobjects->push_back(obj2);

    // create main track
    m_curve = new BezierCurve();
    m_curve->addSmoothHandlePoint(-2, -1, 0);
    m_curve->addSmoothHandlePoint(-1, 0, 0);
    m_curve->addSmoothHandlePoint(0, 1, 0);
    m_curve->addSmoothHandlePoint(1, 2, 0);
    m_curve->addSmoothHandlePoint(0, 1, 0);
    m_curve->addSmoothHandlePoint(1, 2, 0);

    // placing camera on track
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
        //canFire = false;
        if (m_canFire)  {
            Vector3 dir(-Vector3::fromAngles(m_camera->theta, m_camera->phi));
            dir = dir / 100000.0;
            spawnProjectile(dir);
            m_canFire = false;
        }
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
               m_camera->center = m_curve->cubicSample(m.t);
            } else {
               m.gameObj->setPosition(m.curve->cubicSample(m.t));
            }
        }
        sleep(FRAME_RATE);
    }
}

void GameEngine::spawnProjectile(Vector3 dir) {
    GameObject *obj = new GameObject(m_models["models/sphere.obj"]);
    obj->getPosition().x = m_camera->center.x;
    obj->getPosition().y = m_camera->center.y;
    obj->getPosition().z = m_camera->center.z;
    obj->setVelocity(dir);
    m_gobjects->push_back(obj);

}
