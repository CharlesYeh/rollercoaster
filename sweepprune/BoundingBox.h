#ifndef __BOUNDINGBOX_H__
#define __BOUNDINGBOX_H__

#include "math/vector.h"
class GameObject;

class BoundingBox
{
public:


private:
    GameObject *m_gobj;

    Vector3 m_position;
    Vector3 m_dimensions;
};

#endif
