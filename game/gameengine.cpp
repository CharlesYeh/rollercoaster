#include "gameengine.h"
using namespace std;
GameEngine::GameEngine(QObject *parent)
{

    m_canFire = false;

    m_shake = false;
    m_curNumShakes = 0;
    m_refractPeriod = 0;
    m_gobjects = new vector<GameObject*>();
    m_emitters = new vector<ParticleEmitter*>();
    m_curveMounts = new vector<CurveMount>();

    m_pruner = new SweepPruner();
    m_collisions = new set<CollisionPair>();

    m_camera = NULL;

    // load textures
    QImage image, texture;
    QFile file("textures/particle.jpg");
    image.load(file.fileName());
    texture = QGLWidget::convertToGLFormat(image);

    m_textTrail = 0;
    glGenTextures(1, &m_textTrail);
    glBindTexture(GL_TEXTURE_2D, m_textTrail);
    // end load textures

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
}

GameEngine::~GameEngine()
{
    vector<GameObject*>::iterator iter;
    for (iter = m_gobjects->begin(); iter != m_gobjects->end(); iter++)
    {
        delete *iter;
    }
    vector<ParticleEmitter*>::iterator iter2;
    for (iter2 = m_emitters->begin(); iter2 != m_emitters->end(); iter2++)
    {
        delete *iter2;
    }


    delete m_pruner;
    delete m_gobjects;
    delete m_emitters;
    delete m_curveMounts;

    //NOTE: NOT DELETING M_CAMERA BECAUSE OWNED BY GLWIDGET
}

void GameEngine::start()
{
    string objModel = "models/xyzrgb_dragon.obj";
    m_models.insert(pair<std::string,Model>(objModel, ResourceLoader::loadObjModel(objModel.c_str(), 2.0)));

    //------constants--------
    ROCKET_MODEL = "models/missile/missile.obj";

    m_models.insert(pair<std::string,Model>(ROCKET_MODEL, ResourceLoader::loadObjModel(ROCKET_MODEL.c_str(), 1)));


    //GameObject *obj = new GameObject("models/xyzrgb_dragon.obj");
    GameObject *obj = new GameObject(m_models["models/xyzrgb_dragon.obj"]);
    obj->getPosition().y -= 1;
    m_gobjects->push_back(obj);

    GameObject *obj2 = new GameObject(m_models["models/xyzrgb_dragon.obj"]);
    obj2->setVelocity(Vector3(.000002, 0, 0));
    m_gobjects->push_back(obj2);

    // create main track
    m_curve = m_story.getMainCurve();

    // placing camera on track
    m_cameraMount.curve = m_curve;
    m_cameraMount.gameObj = NULL;
    m_cameraMount.t = 0;
    m_curveMounts->push_back(m_cameraMount);

    CurveMount mount;
    mount.curve = m_curve;
    mount.gameObj = obj;
    mount.t = 0;

    m_curveMounts->push_back(mount);

    m_running = true;
    m_stop = false;
    QThread::start();
}

void GameEngine::run()
{
    while (true)
    {
        if (m_stop) {
            m_running = false;
            return;
        }

        if (m_canFire)  {
            spawnProjectile(m_projectileDir);
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

        //---shaking camera if necessary---
        if (m_shake && m_curNumShakes < MAX_SHAKES) {
            float mag = (MAX_SHAKES - m_curNumShakes) / ((float) MAX_SHAKES);
            m_camera->jitterCamera(mag);
            m_curNumShakes++;
        } else {
            m_curNumShakes = 0;
            m_shake = false;
        }

        m_pruner->sweepAndPrune(*m_collisions);

        //---cleaning up and removing emitters/objects
        cleanupObjects();

        m_refractPeriod -= 0.00001;
        sleep(FRAME_RATE);
    }
}

void GameEngine::fireProjectile(Vector3 dir) {
    if (m_refractPeriod < 0) {
        m_canFire = true;
        m_refractPeriod = 1;
        dir.normalize();
        dir = dir / 30000.0;
        m_projectileDir = dir;

        //NOTE: CANNOT SPAWN PROJECTILE HERE: POTENTIALLY DANGEROUS AND CRASHES

        /*
        m_refractPeriod = 1;
        dir.normalize();
        dir = dir / 10000.0;
        spawnProjectile(dir);
        */
    }
}

void GameEngine::spawnProjectile(Vector3 dir) {
    ParticleEmitter *pe = new ProjectileTrail(m_camera, m_camera->center, m_textTrail);
    m_emitters->push_back(pe);

    Projectile *obj = new Projectile(m_models[ROCKET_MODEL], pe);

    //setting up rotation angle for drawing
    Vector3 orthVec = dir.cross(Vector3(5,0,0));
    float angle = -acos(dir.dot(Vector3(1,0,0)) / dir.length()) * 180.0 / 3.14 + 180.0;
    obj->setRotation(orthVec, angle);

    obj->setPosition(m_camera->center);
    obj->setVelocity(dir);
    obj->setIsProjectile();
    m_gobjects->push_back(obj);


    // explosion TESTING###########################
    ParticleEmitter *e = new Explosion(m_camera, m_camera->center, m_textTrail);
    m_emitters->push_back(e);
}

void GameEngine::cleanupObjects() {
    //std::cout << m_gobjects->size() << std::endl;
    mutex.lock();
    for (int i = m_gobjects->size()-1; i >= 0; i--) {
        GameObject *obj = m_gobjects->at(i);
        if (!obj->getIsAlive()) {
            delete obj;
            m_gobjects->erase(m_gobjects->begin()+i);
        }
    }
    for (int i = m_emitters->size()-1; i >= 0; i--) {
        ParticleEmitter *pe = m_emitters->at(i);
        if (!pe->getIsAlive()) {
            delete pe;
            m_emitters->erase(m_emitters->begin()+i);
        }
    }

    mutex.unlock();
}


void GameEngine::stop()
{
    m_stop = true;
}

bool GameEngine::running()
{
    return m_running;
}

QString GameEngine::getStory()
{
    return m_currStory;
}
