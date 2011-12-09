#include "CollisionPair.h"
CollisionPair::CollisionPair(GameObject *g1, GameObject *g2)
{
    if (g1 < g2) {
        m_obj1 = g1;
        m_obj2 = g2;
    }
    else {
        m_obj1 = g2;
        m_obj2 = g1;
    }
}
bool CollisionPair::equals(CollisionPair &pair)
{
    return pair.m_obj1 == m_obj1 && pair.m_obj2 == m_obj2;
}

bool CollisionPair::operator<(const CollisionPair &right) const
{
    return 0 < right.m_obj1 - m_obj1 + right.m_obj2 - m_obj2;
}
