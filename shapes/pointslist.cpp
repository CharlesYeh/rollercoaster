#include "pointslist.h"
#include "math/CS123Matrix.h"
#include "math/CS123Vector.h"

PointsList::PointsList() {
    m_x = new vector<float>();
    m_y = new vector<float>();
    m_z = new vector<float>();
}

PointsList::~PointsList() {
    delete m_x;
    delete m_y;
    delete m_z;
}

void PointsList::addPoint(float x, float y, float z) {
    m_x->push_back(x);
    m_y->push_back(y);
    m_z->push_back(z);
}

void PointsList::clearList() {
    m_x->clear();
    m_y->clear();
    m_z->clear();
}

float PointsList::getPointX(int i) {
    return (*m_x)[i];
}

float PointsList::getPointY(int i) {
    return (*m_y)[i];
}

float PointsList::getPointZ(int i) {
    return (*m_z)[i];
}

int PointsList::getSize() {
    return m_x->size();
}

float *PointsList::getPoints() {
    float *points = new float[m_x->size() * 4];

    for (unsigned int i = 0; i < m_x->size(); i++) {
        points[4 * i + 0] = (*m_x)[i];
        points[4 * i + 1] = (*m_y)[i];
        points[4 * i + 2] = (*m_z)[i];
    }

    return points;
}
