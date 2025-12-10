#include "pch.h"
#include "SubUIManager.h"

void SubUIManager::Update(HWND hWnd)
{
    if (_elements.empty())
        return;

    for (size_t i = 0; i < _elements.size(); ++i)
    {
        auto* elem = _elements[i];

        if (!elem)
        {
            continue;
        }

        uintptr_t ptr = reinterpret_cast<uintptr_t>(elem);
        if (ptr == 0xdddddddd || ptr == 0xfefefefe || ptr == 0xffffffff || ptr < 0x10000)
        {
            continue;
        }

        try
        {
            elem->Update();
        }
        catch (...)
        {   
        }
    }

    ProcessRemovals();
}


void SubUIManager::Render(HDC hDC)
{
    for (auto* elem : _elements)
    {
        if (elem && elem->IsVisible())
        {
            elem->Render(hDC);
        }
    }
}

void SubUIManager::Add(UIElement* elem)
{
    if (!elem) return;

    uintptr_t ptr = reinterpret_cast<uintptr_t>(elem);
    if (ptr == 0xdddddddd || ptr == 0xfefefefe || ptr == 0xffffffff || ptr < 0x10000)
        return;

    _elements.push_back(elem);
}


void SubUIManager::Remove(UIElement* elem)
{
    if (elem)
        _removeList.push_back(elem);
}

void SubUIManager::Clear()
{
    for (auto*& elem : _elements)
    {
        if (elem)
        {
            delete elem;
            elem = nullptr;
        }
    }
    _elements.clear();
    _removeList.clear();
}


void SubUIManager::ProcessRemovals()
{
    for (auto* elem : _removeList)
    {
        auto it = std::find(_elements.begin(), _elements.end(), elem);
        if (it != _elements.end())
        {
            if (*it) {
                delete* it;
                *it = nullptr;
            }
            _elements.erase(it);
        }
    }
    _removeList.clear();
}

