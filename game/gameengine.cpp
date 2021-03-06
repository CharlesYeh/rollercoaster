#include "gameengine.h"
#include "matrix3x3.h"

using namespace std;
GameEngine::GameEngine(QObject *parent)
{
    m_hits          = 0;
    m_fired         = 0;
    m_canFire       = false;
    m_turnCamera    = true;
    m_hitpause      = false;

    m_curNumShakes  = 0;
    m_refractPeriod = 0;
    m_shake         = false;
    m_gobjects      = new vector<GameObject*>();
    m_emitters      = new vector<ParticleEmitter*>();
    m_curveMounts   = new vector<CurveMount>();

    m_pruner        = new SweepPruner();
    m_collisions    = new set<CollisionPair>();
    m_models        = new map<string, Model>();

    m_projectiles   = new vector<Projectile*>();
    m_explosions    = new vector<Explosion*>();

    m_camera        = 0;

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
    delete m_collisions;
    delete m_gobjects;
    delete m_emitters;

    for (unsigned int i = 0; i < m_curveMounts->size(); i++) {
        delete m_curveMounts->at(i).curve;
    }
    delete m_curveMounts; // needs to delete bezier curves!

    delete m_models;

    delete m_projectiles;
    delete m_explosions;

    //NOTE: NOT DELETING M_CAMERA BECAUSE OWNED BY GLWIDGET
}

void GameEngine::start()
{
    //------constants--------
    SHIP_MODEL = "models/ship/f.obj";
    m_models->insert(pair<std::string,Model>(SHIP_MODEL, ResourceLoader::loadObjModel(SHIP_MODEL.c_str(), 2.0)));
    ROCKET_MODEL = "models/missile/missile.obj";
    m_models->insert(pair<std::string,Model>(ROCKET_MODEL, ResourceLoader::loadObjModel(ROCKET_MODEL.c_str(), 1)));


    //setting up projectiles + their emitters
    for (int i = 0; i < NUM_ROCKETS; i++)  {

        m_projectiles->push_back(new Projectile((*m_models)[ROCKET_MODEL], new ProjectileTrail(m_camera, m_camera->center,m_textTrail)));
        m_projectiles->at(i)->setIsAlive(false);
        m_projectiles->at(i)->setIsProjectile();
        m_projectiles->at(i)->getEmitter()->setIsAlive(false);
        m_emitters->push_back(m_projectiles->at(i)->getEmitter());
        m_gobjects->push_back(m_projectiles->at(i));
        m_pruner->addObject(m_projectiles->at(i));
    }

    //setting up explosions
    for (int i = 0; i < NUM_EXPLOSIONS; i++) {
        m_explosions->push_back(new Explosion(m_camera, m_camera->center, m_textTrail));
        m_explosions->at(i)->setIsAlive(false);
        m_emitters->push_back(m_explosions->at(i));
    }

    // placing camera on track
    m_cameraMount.curve = generateCurve(100, 80);
    m_cameraMount.gameObj = NULL;
    m_cameraMount.t = 0;
    m_cameraMount.tChange = 0.0001;
    m_curveMounts->push_back(m_cameraMount);

    spawnCurveEnemies(NUM_ENEMIES);

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

            m_fired++;
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
            m.t += m.tChange;

            //first item in m_curveMounts is for the camera.
            if (iter2 == m_curveMounts->begin()) {
                //rotate camera <##>
                if (m_turnCamera) {
                    Vector3 oldPos = m_camera->realCenter;
                    Vector3 newPos = m.curve->cubicSample(m.t);

                    Vector3 vel = oldPos - newPos;
                    vel.normalize();

                    //Vector3 orthVec = vel.cross(Vector3(0,0,-1));

                    float theta = atan2(vel.z, vel.x);
                    float phi = atan2(vel.y, sqrt(vel.z * vel.z + vel.x * vel.x));

                    // set up vector
                    double rad = theta + M_PI / 2;
                    Vector3 ax = Vector3::fromAngles(fmod(rad, 2 * M_PI), 0);
                    Matrix3x3 rot = getRotMat(ax, phi);

                    m_camera->theta = theta;
                    m_camera->phi = phi;
                    m_camera->up = rot * Vector3(0, 1, 0);
                }
                //rotate camera <##>

                m_camera->setPosition(m.curve->cubicSample(m.t));
            } else {
                //if a game object, update game objects rotation + position
                Vector3 oldPos = m.gameObj->getPosition();
                Vector3 newPos = m.curve->cubicSample(m.t);
                Vector3 vel = newPos - oldPos;
                vel.normalize();

                Vector3 orthVec = vel.cross(Vector3(0,0,-1));
                float angle = -acos(vel.dot(Vector3(0,0,-1)) / vel.length()) * 180.0 / 3.14 + 180.0;
                m.gameObj->setRotation(orthVec, angle);

                m.gameObj->setPosition(m.curve->cubicSample(m.t));
            }

        }


        //handle sweeping and pruning! kill objects that collide, and cause an explosion.
        this->mutex.lock();
        m_pruner->sweepAndPrune(*m_collisions);

        for (set<CollisionPair>::iterator iter = m_collisions->begin(); iter != m_collisions->end(); iter++) {
            CollisionPair p = *iter;

            // collision between live objects!
            if ((p.m_obj1->getIsAlive() && p.m_obj2->getIsAlive()) && (p.m_obj1->getIsProjectile() || p.m_obj2->getIsProjectile())) {

                //find an explosion we can use
                for (unsigned int i = 0; i < m_explosions->size(); i++) {
                    Explosion* exp = m_explosions->at(i);
                    if (!exp->getIsAlive()) {
                        exp->setPosition((p.m_obj1->getPosition() + p.m_obj2->getPosition()) / 2.0);
                        exp->initParticles();
                        exp->setIsAlive(true);

                        Vector3 dist = exp->getPosition() - m_camera->center;
                        float d = dist.length();
                        m_shake = true;

                        m_curNumShakes = d;
                        break;
                    }
                }

                m_hits++;
                if (m_hitpause) {
                    QThread::sleep(1);
                }

                p.m_obj1->setIsAlive(false);
                p.m_obj2->setIsAlive(false);
            }
        }
        this->mutex.unlock();

        //---shaking camera if necessary---
        if (m_shake && m_curNumShakes < MAX_SHAKES) {
            float mag = (MAX_SHAKES - m_curNumShakes) / ((float) MAX_SHAKES);
            m_camera->jitterCamera(mag);
            m_curNumShakes++;
        } else {
            m_curNumShakes = 0;
            m_shake = false;
        }

        m_refractPeriod -= REFRACT_SPEED;
        //sleep(FRAME_RATE);
    }
}

void GameEngine::spawnCurveEnemies(int numEnemies) {
    //just generate numEnemies randomly and places them on curves
    for (int i = 0; i < numEnemies; i++) {
        BezierCurve* curve = generateCurve(100, 140);
        CurveMount mount;
        mount.curve = curve;
        mount.gameObj = new GameObject((*m_models)[SHIP_MODEL]);
        mount.t = 0;

        mount.tChange = rand() % 100 / 1000000.f;  //0.00001;

        m_curveMounts->push_back(mount);
        m_gobjects->push_back(mount.gameObj);
        m_pruner->addObject(mount.gameObj);
    }
}

BezierCurve* GameEngine::generateCurve(int numPoints, int sizeCurve) {
    BezierCurve *curve = new BezierCurve();
    float randX, randY, randZ;

    for (int j=0; j < numPoints; j++) {
        randX = rand() % sizeCurve - (sizeCurve/2.0);
        randY = rand() % sizeCurve - (sizeCurve/2.0);
        randZ = rand() % sizeCurve - (sizeCurve/2.0);
        curve->addSmoothHandlePoint(randX,randY,randZ);
    }
    return curve;
}


void GameEngine::fireProjectile(Vector3 dir) {
    if (m_refractPeriod < 0) { //Only allow firing if refractory period is < 0 (to prevent rockets from self colliding)
        m_canFire = true; //NOTE: we don't actually call spawnProjectile here. just tell the gameengine main loop too (or else weird errors)
        m_refractPeriod = 1;
        dir.normalize();
        dir = dir * PROJECTILE_SPEED;
        m_projectileDir = dir;
    }
}

void GameEngine::spawnProjectile(Vector3 dir) {
    //Creates a projectile!
    Projectile* obj;
    bool foundProjectile = false;

    for (unsigned int i = 0; i < m_projectiles->size(); i ++) {
        if (!m_projectiles->at(i)->getIsAlive()) {
               obj= m_projectiles->at(i);
               foundProjectile = true;
               break;
        }
    }
    if (!foundProjectile)
        return;

    obj->setIsAlive(true);
    obj->resetLifetime();

    obj->getEmitter()->setPosition(m_camera->center);
    obj->getEmitter()->initParticles();
    obj->getEmitter()->setIsAlive(true);

    //setting up rotation angle for drawing
    Vector3 orthVec = dir.cross(Vector3(5,0,0));
    float angle = -acos(dir.dot(Vector3(1,0,0)) / dir.length()) * 180.0 / 3.14 + 180.0;
    obj->setRotation(orthVec, angle);

    obj->setPosition(m_camera->center);
    obj->setVelocity(dir);
    obj->setIsProjectile();
}

void GameEngine::stop()
{
    m_stop = true;
}

bool GameEngine::running()
{
    return m_running;
}
