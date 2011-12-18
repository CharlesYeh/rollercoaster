#ifndef __SWEEPPRUNER_H__
#define __SWEEPPRUNER_H__

#include <list>
#include <set>
#include "BoundingBox.h"
#include "CollisionPair.h"
#include "dimensionpoint.h"
#include "paircomparator.h"

class CollisionPair;

class SweepPruner
{
public:
    SweepPruner();
    virtual ~SweepPruner();

    void sweepAndPrune(std::set<CollisionPair> &pairs);
    void addObject(BoundingBox *obj);
    void removeObject(BoundingBox *obj);

private:
    void sortList(std::list<DimensionPoint*> *pt);
    void getCollisions(std::list<DimensionPoint*> *coords, std::set<CollisionPair> *pairs);
    void sortedInsert(std::list<DimensionPoint*> *l, DimensionPoint *p);

    // lists of bounding box points
    std::list<DimensionPoint*> *m_x;
    std::list<DimensionPoint*> *m_y;
    std::list<DimensionPoint*> *m_z;

};

#endif
