#include "SweepPruner.h"
#include "CollisionPair.h"
#include <set>
#include <algorithm>

using namespace std;

void SweepPruner::sweepAndPrune(set<CollisionPair> &final_pairs)
{
    // adjust list sortedness
    sortList(m_x);
    sortList(m_y);
    sortList(m_z);

    // traverse lists
    set<CollisionPair> pair_x;
    set<CollisionPair> pair_y;
    set<CollisionPair> pair_z;

    getCollisions(m_x, pair_x);
    getCollisions(m_y, pair_y);
    getCollisions(m_z, pair_z);
    
    set<CollisionPair>::iterator iter;
    for (iter = pair_x.begin(); iter != pair_x.end(); iter++) {
        const CollisionPair &p = *iter;
	if (pair_y.find(p) == pair_y.end() || pair_z.find(p) == pair_z.end()) {
            continue;
	}
	
	final_pairs.insert(p);
    }
}

void SweepPruner::getCollisions(list<DimensionPoint*> *coords, set<CollisionPair> &pairs)
{
    set<BoundingBox*> starts;

    list<DimensionPoint*>::iterator iterX;
    for (iterX = coords->begin(); iterX != coords->end(); iterX++) {
        DimensionPoint *p = *iterX;
        if (p->type == START) {
            // if starts isn't empty, then collision!
            std::set<BoundingBox*>::iterator iterc;
            for (iterc = starts.begin(); iterc != starts.end(); iterc++) {
                pairs.insert(CollisionPair(p->object, *iterc));
            }

            starts.insert(p->object);
        }
        else {
            starts.erase(p->object);
        }
    }
}

void SweepPruner::sortList(list<DimensionPoint*> *pt)
{
    /*list<DimensionPoint*>::iterator iter;

    // start at second index
    iter = pt.begin();
    float prevValue = (*iter)->value;
    iter++;

    while (iter != pt.end()) {
        DimensionPoint *dp = (*iter);
        float curValue = dp->value;

        if (prevValue > cur) {
            // go left to find swap point!!
            list<DimensionPoint*>::riter = iter;

            riter--;
            while (riter != pt.start() && (*riter)->value > curValue) {
                riter--;
            }
        }
    }*/
}

void SweepPruner::addObject(BoundingBox *obj)
{
    // add object
    DimensionPoint *sx = obj->getDimensionPointXStart();
    DimensionPoint *sy = obj->getDimensionPointYStart();
    DimensionPoint *sz = obj->getDimensionPointZStart();

    DimensionPoint *ex = obj->getDimensionPointXEnd();
    DimensionPoint *ey = obj->getDimensionPointYEnd();
    DimensionPoint *ez = obj->getDimensionPointZEnd();

    /*list<DimensionPoint*>::iterator iter;
    for (iter = m_x->begin(); iter != m_x->end(); iter++) {
        if (*iter 
    }*/
}
