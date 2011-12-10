#ifndef __COLLISIONPAIR_H__
#define __COLLISIONPAIR_H__

class BoundingBox;

class CollisionPair
{
public:
    CollisionPair(BoundingBox *g1, BoundingBox *g2);
    bool equals(CollisionPair &pair);
    bool operator<(const CollisionPair &right) const;

    BoundingBox *m_obj1, *m_obj2;
};

#endif
