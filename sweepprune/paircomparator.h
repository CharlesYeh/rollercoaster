#ifndef PAIRCOMPARATOR_H
#define PAIRCOMPARATOR_H

#include "CollisionPair.h"
#include <iostream>
using namespace std;

struct PairComparator {
    bool operator()(const CollisionPair &first, const CollisionPair &second) {
        if (((int)first.m_obj1) == ((int)second.m_obj1) && ((int)first.m_obj2) == ((int)second.m_obj2)) {
            cout << first.m_obj1 << " " << second.m_obj1 << endl;
        }
        return ((int)first.m_obj1) == ((int)second.m_obj1) && ((int)first.m_obj2) == ((int)second.m_obj2);
    }
};

#endif // PAIRCOMPARATOR_H
