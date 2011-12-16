#include "BoundingBox.h"
#include <QtOpenGL>

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
    glColor3f(1, 1, 1);
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
