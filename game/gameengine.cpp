#include "gameengine.h"

using namespace std;
GameEngine::GameEngine(QObject *parent)
{
    m_canFire = false;
    m_shake = false;
    m_curNumShakes = 0;
    m_gobjects = new vector<GameObject*>();
    m_curveMounts = new vector<CurveMount>();
    m_camera = NULL;

    string objModel = "models/xyzrgb_dragon.obj";
    m_models.insert(pair<std::string,Model>(objModel, ResourceLoader::loadObjModel(objModel.c_str(), 2.0)));

    //------constants--------
    ROCKET_MODEL = "models/missile/missile.obj";

    m_models.insert(pair<std::string,Model>(ROCKET_MODEL, ResourceLoader::loadObjModel(ROCKET_MODEL.c_str(), 1)));
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

    // add emitter
    m_emitter = new ParticleEmitter();

    QThread::start();
}

void GameEngine::run()
{
    while (true)
    {
        if (m_canFire)  {
            Vector3 dir(-Vector3::fromAngles(m_camera->theta, m_camera->phi));
            dir = dir / 10000.0;
            spawnProjectile(dir);
            m_canFire = false;

            //m_shake = true;
            //m_curNumShakes = 0;
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

        //------------------particles------------------
        m_emitter->updateParticles();

        //---shaking camera if necessary---
        if (m_shake && m_curNumShakes < MAX_SHAKES) {
            float mag = (MAX_SHAKES - m_curNumShakes) / ((float) MAX_SHAKES);
            m_camera->jitterCamera(mag);
            m_curNumShakes++;
        } else {
            m_curNumShakes = 0;
            m_shake = false;
        }

        sleep(FRAME_RATE);
    }
}

void GameEngine::spawnProjectile(Vector3 dir) {
    GameObject *obj = new GameObject(m_models[ROCKET_MODEL]);
    obj->setPosition(m_camera->center);
    obj->setVelocity(dir);
    obj->setIsProjectile();
    m_gobjects->push_back(obj);

}
