#include "pch.h"
#include "Object.h"
#include "InputManager.h"
#include "Component.h"

Object::Object() : m_isDie(false)
{

}

Object::~Object()
{
    for (Component* com : m_vecComponents)
    {
        SAFE_DELETE(com);
    }
    m_vecComponents.clear();
}

void Object::Update()
{
   
}

void Object::LateUpdate()
{
    for (Component* com : m_vecComponents)
    {
        if (com != nullptr)
            com->LateUpdate();
    }
}


void Object::Render(HDC _hdc)
{
    //RECT_RENDER(_hdc, _pos.x, _pos.y, _size.x, _size.y);
}

void Object::ComponentRender(HDC hdc)
{
    for (Component* com : m_vecComponents)
    {
        if (com != nullptr)
            com->Render(hdc);
    }
}
