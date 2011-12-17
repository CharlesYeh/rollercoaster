#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "math/vector.h"
#include <vector>

/*
 * A list of points is kept, where every third point including the first are control points.
 * The other points are handle points.
 *
 */
class BezierCurve
{
public:
    BezierCurve();
    virtual ~BezierCurve();

    void addPoint(float x, float y, float z);
    void addPoint(Vector3 v);

    void addSmoothHandlePoint(float x, float y, float z);

    //Vector3 quadraticSample(float t);
    Vector3 cubicSample(float t);


private:
    int m_curStart;
    std::vector<Vector3> *m_points;
};

#endif // BEZIERCURVE_H
