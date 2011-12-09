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

Vector3 BezierCurve::quadraticSample(float t)
{
    int pt = (int) t;

    float ts = t - pt;
    float tf = 1 - ts;

    if (t < 0 || t >= m_points->size() - 2)
    {
        return Vector3();
    }

    Vector3 p0 = (*m_points)[pt];
    Vector3 p1 = (*m_points)[pt + 1];
    Vector3 p2 = (*m_points)[pt + 2];

    return tf * (tf * p0 + ts * p1) + ts * (tf * p1 + t * p2);
}

Vector3 BezierCurve::cubicSample(float t)
{
    return Vector3();
}
