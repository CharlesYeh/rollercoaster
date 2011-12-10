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
    setPosition(getPosition() + m_velocity);
}
