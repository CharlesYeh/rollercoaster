#include "gameobject.h"

GameObject::GameObject(Model model)
{
   m_model = model;
}

GameObject::GameObject(QString str)
{
    //m_model = ResourceLoader::loadObjModel(str);
}

GameObject::~GameObject() {
}

void GameObject::act()
{
    m_position.x += m_actDir.x;
    m_position.y += m_actDir.y;
    m_position.z += m_actDir.z;
}
