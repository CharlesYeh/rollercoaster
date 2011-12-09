#ifndef __COLLISIONPAIR_H__
#define __COLLISIONPAIR_H__

#include "game/gameobject.h"

class CollisionPair
{
public:
    CollisionPair(GameObject *g1, GameObject *g2);
    bool equals(CollisionPair &pair);
    bool operator<(const CollisionPair &right) const;

    GameObject *m_obj1, *m_obj2;
};

#endif
