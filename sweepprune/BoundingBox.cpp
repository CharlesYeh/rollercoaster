#include "BoundingBox.h"

//#include "<vector>"
#include <QtOpenGL>
#include "matrix3x3.h"

using namespace std;

BoundingBox::BoundingBox()
{
    m_xstart.object = m_ystart.object = m_zstart.object = m_xend.object = m_yend.object = m_zend.object = this;

    m_xstart.type = m_ystart.type = m_zstart.type = START;
    m_xend.type = m_yend.type = m_zend.type = END;

    setPosition(Vector3());
}

void BoundingBox::setDimension(float x, float y, float z)
{
    m_base.x = m_dimension.x = x / 2;
    m_base.y = m_dimension.y = y / 2;
    m_base.z = m_dimension.z = z / 2;

    setPosition(m_position);
}

void BoundingBox::setRotation(Vector3 rotate, float angle)
{
    Matrix3x3 m = getRotMat(rotate, angle * M_PI / 180);

    // get new bounding box;
    float sx = -m_base.x;
    float sy = -m_base.y;
    float sz = -m_base.z;

    float ex = m_base.x;
    float ey = m_base.y;
    float ez = m_base.z;

    Vector3 p1(sx, sy, sz);
    Vector3 p2(ex, sy, sz);
    Vector3 p3(sx, ey, sz);
    Vector3 p4(ex, ey, sz);
    Vector3 p5(sx, sy, ez);
    Vector3 p6(ex, sy, ez);
    Vector3 p7(sx, ey, ez);
    Vector3 p8(ex, ey, ez);

    vector<Vector3> points;

    points.push_back(m * p1);
    points.push_back(m * p2);
    points.push_back(m * p3);
    points.push_back(m * p4);
    points.push_back(m * p5);
    points.push_back(m * p6);
    points.push_back(m * p7);
    points.push_back(m * p8);

    m1 = m * p1;
    m2 = m * p2;
    m3 = m * p3;
    m4 = m * p4;
    m5 = m * p5;
    m6 = m * p6;
    m7 = m * p7;
    m8 = m * p8;

    float minx, miny, minz, maxx, maxy, maxz;

    for (unsigned int i = 0; i < points.size(); i++) {
        Vector3 &p = points[i];

        if (i == 0 || p.x < minx)
            minx = p.x;
        if (i == 0 || p.y < miny)
            miny = p.y;
        if (i == 0 || p.z < minz)
            minz = p.z;
        if (i == 0 || p.x > maxx)
            maxx = p.x;
        if (i == 0 || p.y > maxy)
            maxy = p.y;
        if (i == 0 || p.z > maxz)
            maxz = p.z;
    }

    m_dimension.x = (maxx - minx) / 2;
    m_dimension.y = (maxy - miny) / 2;
    m_dimension.z = (maxz - minz) / 2;

    /*m_xstart.value = minx + m_position.x;
    m_ystart.value = miny + m_position.y;
    m_zstart.value = minz + m_position.z;
    m_xend.value = maxx + m_position.x;
    m_yend.value = maxy + m_position.y;
    m_zend.value = maxz + m_position.z;*/
    //cout << "END " << minx << " " << miny << " " << minz << endl;

    setPosition(m_position);
    m_rotation = rotate; m_angle = angle;
}

void BoundingBox::setPosition(Vector3 pos)
{
    m_position = pos;

    m_xstart.value = pos.x - m_dimension.x;
    m_ystart.value = pos.y - m_dimension.y;
    m_zstart.value = pos.z - m_dimension.z;

    m_xend.value = pos.x + m_dimension.x;
    m_yend.value = pos.y + m_dimension.y;
    m_zend.value = pos.z + m_dimension.z;
}

bool BoundingBox::collidesWith(BoundingBox &box) {
    return (box.m_position.x - box.m_dimension.x < m_position.x + m_dimension.x && box.m_position.x + box.m_dimension.x > m_position.x - m_dimension.x) &&
           (box.m_position.y - box.m_dimension.y < m_position.y + m_dimension.y && box.m_position.y + box.m_dimension.y > m_position.y - m_dimension.y) &&
           (box.m_position.z - box.m_dimension.z < m_position.z + m_dimension.z && box.m_position.z + box.m_dimension.z > m_position.z - m_dimension.z);
}

void BoundingBox::drawBoundingBox()
{
    glShadeModel(GL_FLAT);
    glBegin(GL_LINE_STRIP);
    // front face
    glVertex3f(m_xstart.value, m_ystart.value, m_zstart.value);
    glVertex3f(m_xend.value, m_ystart.value, m_zstart.value);
    glVertex3f(m_xend.value, m_yend.value, m_zstart.value);
    glVertex3f(m_xstart.value, m_yend.value, m_zstart.value);
    glVertex3f(m_xstart.value, m_ystart.value, m_zstart.value);

    // end face
    glVertex3f(m_xstart.value, m_ystart.value, m_zend.value);
    glVertex3f(m_xend.value, m_ystart.value, m_zend.value);
    glVertex3f(m_xend.value, m_yend.value, m_zend.value);
    glVertex3f(m_xstart.value, m_yend.value, m_zend.value);
    glVertex3f(m_xstart.value, m_ystart.value, m_zend.value);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(m_xend.value, m_ystart.value, m_zstart.value);
    glVertex3f(m_xend.value, m_ystart.value, m_zend.value);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(m_xend.value, m_yend.value, m_zstart.value);
    glVertex3f(m_xend.value, m_yend.value, m_zend.value);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(m_xstart.value, m_yend.value, m_zstart.value);
    glVertex3f(m_xstart.value, m_yend.value, m_zend.value);
    glEnd();
    glShadeModel(GL_SMOOTH);
}

void BoundingBox::drawRotationPoints()
{

    glShadeModel(GL_FLAT);
    glBegin(GL_POINTS);
    glPointSize(3);

    glVertex3fv((m1 + m_position).xyz);
    glVertex3fv((m2 + m_position).xyz);
    glVertex3fv((m3 + m_position).xyz);
    glVertex3fv((m4 + m_position).xyz);
    glVertex3fv((m5 + m_position).xyz);
    glVertex3fv((m6 + m_position).xyz);
    glVertex3fv((m7 + m_position).xyz);
    glVertex3fv((m8 + m_position).xyz);

    glEnd();
}
