#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "resourceloader.h"
#include "math/vector.h"

class GameObject
{
public:
    GameObject(QString str);
    virtual ~GameObject() {};

    Model &getModel() { return m_model; };
    Vector3 &getPosition() { return m_position; };
    Vector3 &getActDir() { return m_actDir; };
    Vector3 &getRotation() { return m_rotation; };

    void setPosition(Vector3 pos) { m_position = pos; };
    void setActDir(Vector3 dir) { m_actDir = dir; };

    void act();


private:
    Model m_model;

    Vector3 m_position;
    Vector3 m_rotation;
    Vector3 m_actDir;
};

#endif // GAMEOBJECT_H
