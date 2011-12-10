#ifndef __SWEEPPRUNER_H__
#define __SWEEPPRUNER_H__

#include <list>
#include <set>
#include "BoundingBox.h"
#include "CollisionPair.h"
#include "dimensionpoint.h"

class CollisionPair;

class SweepPruner
{
public:
    void sweepAndPrune(std::set<CollisionPair> &pairs);
    void addObject(BoundingBox *obj);

private:
    void getCollisions(std::list<DimensionPoint*> *coords, std::set<CollisionPair> &pairs);
    void sortList(std::list<DimensionPoint*> *pt);

    std::list<DimensionPoint*> *m_x;
    std::list<DimensionPoint*> *m_y;
    std::list<DimensionPoint*> *m_z;

};

#endif
