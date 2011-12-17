#include "storyline.h"
#include "beziercurve.h"

Storyline::Storyline()
{
    m_curve = new BezierCurve();

    m_curve->addSmoothHandlePoint(-2, -1, 0);
    m_curve->addSmoothHandlePoint(-1, 0, 0);
    m_curve->addSmoothHandlePoint(0, 1, 0);
    m_curve->addSmoothHandlePoint(1, 2, 0);
    m_curve->addSmoothHandlePoint(0, 1, 0);
    m_curve->addSmoothHandlePoint(1, 2, 0);

    m1 = new QString("This your first flight? Don't worry, you're with the best pilot in the fleet!");
    m2 = new QString("Just don't forget to aim and fire with the mouse button.");
    m3 = new QString("There they are! Go!");
    m4 = new QString("Help!! I've got one on my tail. I can't shake it off.");
    m5 = new QString("Let's help this gent out.");
}

QString *Storyline::getFullText(float t)
{
    if (t < 1) {
        return m1;
    }
    else if (t < 5) {
        return m2;
    }
    else if (t < 10) {
        return m3;
    }
    else if (t < 15) {
        return m4;
    }
    else if (t < 20) {
        return m5;
    }
}
