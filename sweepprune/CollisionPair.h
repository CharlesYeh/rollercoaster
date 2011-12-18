#ifndef __COLLISIONPAIR_H__
#define __COLLISIONPAIR_H__

#include <iostream>
using namespace std;

class BoundingBox;

struct CollisionPair
{
    CollisionPair(BoundingBox *g1, BoundingBox *g2) {
        if (g1 < g2) {
            m_obj1 = g1;
            m_obj2 = g2;
        }
        else {
            m_obj1 = g2;
            m_obj2 = g1;
        }
    }

    union {
        struct {
            BoundingBox *m_obj1, *m_obj2;
        };

        double add;
    };

    bool operator==(const CollisionPair &right) const
    {
        return add == right.add;
    }

    bool operator<(const CollisionPair &right) const
    {
        return add < right.add;
    }
};

#endif
