#include "gameengine.h"

using namespace std;
GameEngine::GameEngine(QObject *parent)
{
    m_gobjects = new vector<GameObject*>();
}

GameEngine::~GameEngine()
{
    vector<GameObject*>::iterator iter;
    for (iter = m_gobjects->begin(); iter != m_gobjects->end(); iter++)
    {
        delete *iter;
    }

    delete m_gobjects;
}

void GameEngine::start()
{
    GameObject *obj = new GameObject("models/xyzrgb_dragon.obj");
    m_gobjects->push_back(obj);
    GameObject *obj2 = new GameObject("models/xyzrgb_dragon.obj");
    obj->getPosition().y -= 1;
    m_gobjects->push_back(obj2);
    /*m_gobjects->push_back(new GameObject("models/xyzrgb_dragon.obj"));
    m_gobjects->push_back(new GameObject("models/xyzrgb_dragon.obj"));*/

    QThread::start();
}

void GameEngine::run()
{
    while (true)
    {
        vector<GameObject*>::iterator iter;
        for (iter = m_gobjects->begin(); iter != m_gobjects->end(); iter++)
        {
            (*iter)->act();
        }

        sleep(FRAME_RATE);
    }
}

