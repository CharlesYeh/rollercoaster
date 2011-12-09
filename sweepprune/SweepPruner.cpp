#include "SweepPruner.h"
#include "CollisionPair.h"
#include <set>

using namespace std;

void SweepPruner::sweepAndPrune()
{
    // adjust list sortedness

    // traverse lists
    set<GameObject *> starts;
    set<CollisionPair> pairs;

    list<DimensionPoint>::iterator iterX;
    for (iterX = m_x->begin(); iterX != m_x->end(); iterX++) {
        DimensionPoint p = *iterX;
        if (p.type == START) {
            // if starts isn't empty, then collision!
            std::set<GameObject *>::iterator iterc;
            for (iterc = starts.begin(); iterc != starts.end(); iterc++) {
                pairs.insert(CollisionPair(p.object, *iterc));
            }

            starts.insert(p.object);
        }
        else {
            starts.erase(p.object);
        }
    }
}

void SweepPruner::addObject()
{
    // add object
}
