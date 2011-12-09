#include "gameobject.h"

GameObject::GameObject(QString str)
{
    m_model = ResourceLoader::loadObjModel(str);
}

void GameObject::act()
{
    m_position.x += m_actDir.x;
    m_position.y += m_actDir.y;
    m_position.z += m_actDir.z;
}
