#include "BoundingBox.h"

BoundingBox::BoundingBox
{
    m_xstart.object = m_ystart.object = m_zstart.object = m_xend.object = m_yend.object = m_zend.object = this;

    m_xstart.type = m_ystart.type = m_zstart.type = PointType.START;
    m_xend.type = m_yend.type = m_zend.type = PointType.END;

    setPosition(Vector3());
}

void BoundingBox::setDimension(float x, float y, float z) {
    m_dimension.x = x;
    m_dimension.y = y;
    m_dimension.z = z;

    setPosition(m_position);
}

void BoundingBox::setPosition(Vector3 &pos)
{
    m_position.x = pos.x;
    m_position.y = pos.y;
    m_position.z = pos.z;

    m_xstart.value = pos.x - m_dimension.x;
    m_ystart.value = pos.y - m_dimension.y;
    m_zstart.value = pos.z - m_dimension.z;

    m_xend.value = pos.x + m_dimension.x;
    m_yend.value = pos.y + m_dimension.y;
    m_zend.value = pos.z + m_dimension.z;
}
