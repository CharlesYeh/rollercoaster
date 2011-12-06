#ifndef __POINTSLIST_H__
#define __POINTSLIST_H__

#include <vector>
#include "math/CS123Matrix.h"

using namespace std;

class PointsList
{
public:
    PointsList();
    ~PointsList();

    void addPoint(float x, float y, float z);
    void clearList();
    int getSize();

    float *getPoints();
    float *getPoints(Matrix4x4 &trans);

    float getPointX(int i);
    float getPointY(int i);
    float getPointZ(int i);

private:
    vector<float> *m_x, *m_y, *m_z;
};

#endif // POINTSLIST_H
