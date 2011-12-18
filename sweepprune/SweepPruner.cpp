#include "SweepPruner.h"
#include "CollisionPair.h"
#include <set>
#include <algorithm>

#include <iostream>

using namespace std;

SweepPruner::SweepPruner()
{
    m_x = new list<DimensionPoint*>();
    m_y = new list<DimensionPoint*>();
    m_z = new list<DimensionPoint*>();
}

SweepPruner::~SweepPruner()
{
    delete m_x;
    delete m_y;
    delete m_z;

    m_x = m_y = m_z = 0;
}

void SweepPruner::sweepAndPrune(set<CollisionPair> &final_pairs)
{
    final_pairs.clear();

    if(m_x == 0)
        return;

    // adjust list sortedness
    sortList(m_x);
    sortList(m_y);
    sortList(m_z);

    // traverse lists
    set<CollisionPair> *pair_x = new set<CollisionPair>();
    set<CollisionPair> *pair_y = new set<CollisionPair>();
    set<CollisionPair> *pair_z = new set<CollisionPair>();

    pair_x->clear();
    pair_y->clear();
    pair_z->clear();

    getCollisions(m_x, pair_x);
    getCollisions(m_y, pair_y);
    getCollisions(m_z, pair_z);
    
    // return intersection of all three collision sets
    set<CollisionPair>::iterator iter;
    for (iter = pair_x->begin(); iter != pair_x->end(); iter++) {
        const CollisionPair &p = *iter;

        if (pair_y->find(p) != pair_y->end() && pair_z->find(p) != pair_z->end()) {
            final_pairs.insert(p);
        }
    }

    delete pair_x;
    delete pair_y;
    delete pair_z;
}

void SweepPruner::getCollisions(list<DimensionPoint*> *coords, set<CollisionPair> *pairs)
{
    set<BoundingBox*> *starts = new set<BoundingBox*>();

    list<DimensionPoint*>::iterator iterX;
    float prevValue = (*coords->begin())->value;
    for (iterX = coords->begin(); iterX != coords->end(); iterX++) {
        DimensionPoint *p = *iterX;
        prevValue = p->value;

        if (p->type == START) {
            // if starts isn't empty, then collision!
            std::set<BoundingBox*>::iterator iterc;

            for (iterc = starts->begin(); iterc != starts->end(); iterc++) {
                pairs->insert(CollisionPair(p->object, *iterc));
            }

            starts->insert(p->object);
        }
        else {
            starts->erase(p->object);
        }
    }

    delete starts;
}

void SweepPruner::sortList(list<DimensionPoint*> *pt)
{
    list<DimensionPoint*>::iterator iter;

    // start at second index
    if (pt->size() == 0)
        return;

    iter = pt->begin();
    float prevValue = (*iter)->value;
    iter++;

    while (iter != pt->end()) {
        DimensionPoint *dp = (*iter);
        float curValue = dp->value;

        if (prevValue > curValue) {
            // go left to find swap point!!
            list<DimensionPoint*>::iterator riter = pt->begin();

            while ((*riter)->value < curValue) {
                riter++;
            }

            list<DimensionPoint*>::iterator diter = iter++;

            pt->insert(riter, dp);
            pt->erase(diter);
            iter--;
        }
        else
                prevValue = curValue;
        iter++;
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

    sortedInsert(m_x, sx);
    sortedInsert(m_y, sy);
    sortedInsert(m_z, sz);

    sortedInsert(m_x, ex);
    sortedInsert(m_y, ey);
    sortedInsert(m_z, ez);
}

void SweepPruner::removeObject(BoundingBox *obj)
{
    DimensionPoint *sx = obj->getDimensionPointXStart();
    DimensionPoint *sy = obj->getDimensionPointYStart();
    DimensionPoint *sz = obj->getDimensionPointZStart();

    DimensionPoint *ex = obj->getDimensionPointXEnd();
    DimensionPoint *ey = obj->getDimensionPointYEnd();
    DimensionPoint *ez = obj->getDimensionPointZEnd();

    m_x->remove(sx);
    m_y->remove(sy);
    m_z->remove(sz);

    m_x->remove(ex);
    m_y->remove(ey);
    m_z->remove(ez);
}

void SweepPruner::sortedInsert(list<DimensionPoint*> *l, DimensionPoint *p)
{
    float val = p->value;

    list<DimensionPoint*>::iterator iter;
    for (iter = l->begin(); iter != l->end(); iter++) {
        DimensionPoint *dp = *iter;
        if (dp->value > val) {
            break;
        }
    }

    l->insert(iter, p);
}
