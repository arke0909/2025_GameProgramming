#include "pch.h"
#include "SubUIManager.h"
#include "InputManager.h"

void SubUIManager::Add(UIElement* elem)
{
    _elements.push_back(elem);
}

void SubUIManager::Update(HWND hWnd)
{

    for (auto* elem : _elements)
    {
        elem->Update();
    }
}

void SubUIManager::Render(HDC hdc)
{


    for (auto* elem : _elements)
    {
        elem->Render(hdc);
    }
}


int SubUIManager::Count()
{
	return static_cast<int>(_elements.size());
}

void SubUIManager::Clear()
{
    for (auto* elem : _elements)
        delete elem;

    _elements.clear();
}
