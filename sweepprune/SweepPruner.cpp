#include "SweepPruner.h"
#include "CollisionPair.h"
#include <set>
#include <algorithm>

using namespace std;

void SweepPruner::sweepAndPrune(set<CollisionPair> &final_pairs)
{
    // adjust list sortedness
    m_x->sort();
    m_y->sort();
    m_z->sort();

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
