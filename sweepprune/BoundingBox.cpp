#include "BoundingBox.h"
#include <QtOpenGL>
#include "math/CS123Matrix.h"
#include "math/CS123Vector.h"

BoundingBox::BoundingBox()
{
    m_xstart.object = m_ystart.object = m_zstart.object = m_xend.object = m_yend.object = m_zend.object = this;

    m_xstart.type = m_ystart.type = m_zstart.type = START;
    m_xend.type = m_yend.type = m_zend.type = END;

    setPosition(Vector3());
}

void BoundingBox::setDimension(float x, float y, float z)
{
    m_dimension.x = x / 2;
    m_dimension.y = y / 2;
    m_dimension.z = z / 2;

    setPosition(m_position);
}

void BoundingBox::setRotation(Vector3 rotate, float angle)
{
    Matrix4x4 m = getInvRotMat(Vector4(m_position.x, m_position.y, m_position.z, 1),
                               Vector4(rotate.x,rotate.y, rotate.z, 1), angle);
    // get new bounding box;
    float sx = m_xstart.value;
    float sy = m_ystart.value;
    float sz = m_zstart.value;

    float ex = m_xend.value;
    float ey = m_yend.value;
    float ez = m_zend.value;

    Vector4 p1(sx, sy, sz,1 );
    Vector4 p2(ex, sy, sz,1 );
    Vector4 p3(sx, ey, sz,1 );
    Vector4 p4(ex, ey, sz,1 );
    Vector4 p5(sx, sy, ez,1 );
    Vector4 p6(ex, sy, ez,1 );
    Vector4 p7(sx, ey, ez,1 );
    Vector4 p8(ex, ey, ez,1 );

    vector<Vector4> points;

    points.push_back(m * p1);
    points.push_back(m * p2);
    points.push_back(m * p3);
    points.push_back(m * p4);
    points.push_back(m * p5);
    points.push_back(m * p6);
    points.push_back(m * p7);
    points.push_back(m * p8);

    float minx, miny, minz, maxx, maxy, maxz;

    for (int i = 0; i < points.size(); i++) {
        Vector4 &p = points[i];

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

    m_xstart.value = minx;
    m_ystart.value = miny;
    m_zstart.value = minz;
    m_xend.value = maxx;
    m_yend.value = maxy;
    m_zend.value = maxz;

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

void BoundingBox::drawBoundingBox()
{
    glShadeModel(GL_FLAT);
    glColor3f(1, 0, 0);
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
