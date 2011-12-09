#ifndef __SWEEPPRUNER_H__
#define __SWEEPPRUNER_H__

#include <list>

class GameObject;

enum PointType
{
    START, END
};

struct DimensionPoint
{
    GameObject *object;
    PointType type;
    float value;
};

class SweepPruner
{
public:
    void sweepAndPrune();
    void addObject();

private:
    std::list<DimensionPoint> *m_x;
    std::list<DimensionPoint> *m_y;
    std::list<DimensionPoint> *m_z;

};

#endif
