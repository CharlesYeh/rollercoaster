#include "gameobject.h"

GameObject::GameObject(Model model)
{
   m_model = model;

   GLfloat dims[3];
   glmDimensions(model.model, dims);
   setDimension(dims[0], dims[1], dims[2]);

   m_isProjectile = false;
}

GameObject::~GameObject() {
}

void GameObject::act()
{
    setPosition(getPosition() + m_velocity);
}
