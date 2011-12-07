#include "gameobject.h"

GameObject::GameObject(QString str)
{
    m_model = ResourceLoader::loadObjModel(str);
}

void GameObject::act()
{
    m_position.x += .0000002;
}
