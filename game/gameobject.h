#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "resourceloader.h"
#include "math/vector.h"
#include "sweepprune/BoundingBox.h"

class GameObject : public BoundingBox
{
public:
    GameObject(Model model);
    virtual ~GameObject();

    Model &getModel() { return m_model; }
    Vector3 &getVelocity() { return m_velocity; }
    Vector3 &getRotation() { return m_rotation; }
    float &getAngleRotation() { return m_angle;}
    void setRotation(Vector3 rotate, float angle) { m_rotation = rotate; m_angle = angle;}

    void setVelocity(Vector3 dir) { m_velocity = dir; }
    void setIsProjectile() { m_isProjectile = true;}
    bool getIsProjectile() { return m_isProjectile; }
    bool getIsAlive() { return m_isAlive;}

    virtual void act();

protected:
    bool m_isAlive;
private:
    Model m_model;
    bool m_isProjectile;

    Vector3 m_rotation;
    float m_angle;
    Vector3 m_velocity;
};

#endif // GAMEOBJECT_H
