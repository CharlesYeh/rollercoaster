#include "beziercurve.h"

using namespace std;

BezierCurve::BezierCurve()
{
    m_points = new vector<Vector3>();
}

BezierCurve::~BezierCurve()
{
    delete m_points;
}

void BezierCurve::addPoint(Vector3 v)
{
    m_points->push_back(v);
}

void BezierCurve::addPoint(float x, float y, float z)
{
    m_points->push_back(Vector3(x, y, z));
}

/*
 * Appends a handle point. Adds control points as necessary between the last handle point and the one
 * being added. This way, all control points are added automatically and the curve is continuous.
 */
void BezierCurve::addSmoothHandlePoint(float x, float y, float z)
{
    Vector3 v = Vector3(x, y, z);

    if (m_points->size() % 3 == 0 && m_points->size() > 0) {
        // add control point first
        Vector3 &e = m_points->at(m_points->size() - 1);
        addPoint((v + e) / 2);
    }

    addPoint(v);
}

/*Vector3 BezierCurve::quadraticSample(float t)
{
    int pt = (int) t;

    float ts = t - pt;
    float tf = 1 - ts;

    if (t < 0 || t >= m_points->size() - 2)
    {
        return Vector3();
    }

    // use every other point as a control point
    int pt2 = pt * 2;

    Vector3 p0 = (*m_points)[pt2];
    Vector3 p1 = (*m_points)[pt2 + 1];
    Vector3 p2 = (*m_points)[pt2 + 2];

    return tf * (tf * p0 + ts * p1) + ts * (tf * p1 + ts * p2);
}*/

Vector3 BezierCurve::cubicSample(float t)
{
    int pt = (int) t;
    if (t < 0 || 4 * pt >= m_points->size()) {
        return m_points->at(m_curStart + 3); //return last control point
    }

    // every third point is a control point
    int pt3 = pt * 3;
    m_curStart = pt3;

    Vector3 p0 = m_points->at(pt3);
    Vector3 p1 = m_points->at(pt3 + 1);
    Vector3 p2 = m_points->at(pt3 + 2);
    Vector3 p3 = m_points->at(pt3 + 3);

    float ts = t - pt;
    float tf = 1 - ts;

    return (pow(tf, 3)*p0) + (3*tf*tf*ts*p1) + (3*tf*ts*ts*p2) + (pow(ts,3)*p3);
}
