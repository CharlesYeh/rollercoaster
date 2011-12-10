#ifndef __DIMPOINT_H__
#define __DIMPOINT_H__

class BoundingBox;

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

#endif
