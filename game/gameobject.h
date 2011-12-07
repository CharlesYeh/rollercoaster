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
    Vector3 &getRotation() { return m_rotation; };

    void act();


private:
    Model m_model;

    Vector3 m_position;
    Vector3 m_rotation;
};

#endif // GAMEOBJECT_H
