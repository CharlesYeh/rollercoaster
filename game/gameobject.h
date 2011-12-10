#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "resourceloader.h"
#include "math/vector.h"
#include "sweepprune/BoundingBox.h"

class GameObject : public BoundingBox
{
public:
    GameObject(Model model);
    GameObject(QString str);
    virtual ~GameObject();

    Model &getModel() { return m_model; }
    Vector3 &getVelocity() { return m_velocity; }
    Vector3 &getRotation() { return m_rotation; }

    void setVelocity(Vector3 dir) { m_velocity = dir; }

    void act();


private:
    Model m_model;

    Vector3 m_rotation;
    Vector3 m_velocity;
};

#endif // GAMEOBJECT_H
