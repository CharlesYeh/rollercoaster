#ifndef __BOUNDINGBOX_H__
#define __BOUNDINGBOX_H__

#include "sweepprune/SweepPruner.h"
#include "math/vector.h"
#include "dimensionpoint.h"

/*
 * m_position is the center point of the object.
 * m_dimension specifies the half of width, height, and depth of the object.
 */
class BoundingBox
{
public:
    BoundingBox();

    DimensionPoint *getDimensionPointXStart() { return &m_xstart; };
    DimensionPoint *getDimensionPointYStart() { return &m_ystart; };
    DimensionPoint *getDimensionPointZStart() { return &m_zstart; };

    DimensionPoint *getDimensionPointXEnd() { return &m_xend; };
    DimensionPoint *getDimensionPointYEnd() { return &m_yend; };
    DimensionPoint *getDimensionPointZEnd() { return &m_zend; };

    Vector3 getPosition() { return m_position; };
    Vector3 &getRotation() { return m_rotation; }
    float &getAngleRotation() { return m_angle;}

    void setPosition(Vector3 pos);
    void setDimension(float x, float y, float z);
    void setRotation(Vector3 rotate, float angle);

    virtual void setIsAlive(bool status) { m_isAlive = status;}
    bool getIsAlive() const {return m_isAlive;}

    void drawBoundingBox();
    void setIsProjectile() { m_isProjectile = true;}
    bool getIsProjectile() { return m_isProjectile; }

protected:
    bool m_isAlive;
    bool m_isProjectile;

private:
    DimensionPoint m_xstart, m_ystart, m_zstart,
                   m_xend, m_yend, m_zend;

    Vector3 m_position;
    Vector3 m_dimension, m_base;    // m_base used to approximate rotations

    Vector3 m_rotation;
    float m_angle;
};

#endif
