#ifndef __SWEEPPRUNER_H__
#define __SWEEPPRUNER_H__

#include <list>
#include <set>
#include "BoundingBox.h"
#include "CollisionPair.h"

enum PointType
{
    START, END
};

struct DimensionPoint
{
    BoundingBox *object;
    PointType type;
    float value;
};

class SweepPruner
{
public:
    void sweepAndPrune(std::set<CollisionPair> &pairs);
    void addObject(BoundingBox *obj);

private:
    void getCollisions(std::list<DimensionPoint*> *coords, std::set<CollisionPair> &pairs);

    std::list<DimensionPoint*> *m_x;
    std::list<DimensionPoint*> *m_y;
    std::list<DimensionPoint*> *m_z;

};

#endif
