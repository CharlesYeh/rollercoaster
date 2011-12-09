#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "math/vector.h"
#include <vector>

class BezierCurve
{
public:
    BezierCurve();
    virtual ~BezierCurve();

    Vector3 quadraticSample(float t);
    Vector3 cubicSample(float t);


private:
    std::vector<Vector3> *m_points;
};

#endif // BEZIERCURVE_H
