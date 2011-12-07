#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <QThread>
#include <vector>
#include "gameobject.h"

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
    std::vector<GameObject*> *m_gobjects;
};

#endif // GAMEENGINE_H
