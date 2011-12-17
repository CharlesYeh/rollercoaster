#ifndef STORYLINE_H
#define STORYLINE_H

#include "QString"

class BezierCurve;

class Storyline
{
public:
    Storyline();
    BezierCurve *getMainCurve() { return m_curve; };
    QString *getFullText(float t);

private:
    BezierCurve *m_curve;
    QString *m1, *m2, *m3, *m4, *m5;
};

#endif // STORYLINE_H
