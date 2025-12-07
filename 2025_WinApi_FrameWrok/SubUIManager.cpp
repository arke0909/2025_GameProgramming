#include "pch.h"
#include "SubUIManager.h"
#include "InputManager.h"

void SubUIManager::Add(UIElement* elem)
{
    _elements.push_back(elem);
}

void SubUIManager::Update(HWND hWnd)
{
    if (_elements.empty()) return;

    for (auto* elem : _elements)
    {
        if (elem == nullptr) {
            continue;
        }

        uintptr_t raw = reinterpret_cast<uintptr_t>(elem);
        if (raw == 0xdddddddddddddddd || raw == 0xfeeefeeefeeefeee) {
            continue;
        }

        try {
            elem->Update();
        }
        catch (...) {
        }
    }
}


void SubUIManager::Render(HDC hdc)
{
    if (_elements.empty()) return;

    for (auto* elem : _elements)
    {
        if (elem->IsVisible())
            elem->Render(hdc);
    }
}



int SubUIManager::Count()
{
    return static_cast<int>(_elements.size());
}

void SubUIManager::Clear()
{

    for (auto*& elem : _elements)
    {
        delete elem;
        elem = nullptr;
    }

    _elements.clear();

    _elements.shrink_to_fit();
}

