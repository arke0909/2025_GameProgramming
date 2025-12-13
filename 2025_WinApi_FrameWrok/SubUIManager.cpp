#include "pch.h"
#include "SubUIManager.h"
#include "UIElement.h"

void SubUIManager::Update(HWND hWnd)
{

    ProcessRemovals();

    if (_elements.empty())
        return;

    for (size_t i = 0; i < _elements.size(); ++i)
    {
        UIElement* elem = _elements[i];

        if (!elem)
            continue;


        if (std::find(_removeList.begin(), _removeList.end(), elem) != _removeList.end())
            continue;

        try
        {
            elem->Update();
        }
        catch (...)
        {
            std::cerr << "[Error] elem->Update() 예외 발생\n";
        }
    }


    ProcessRemovals();
}

void SubUIManager::Render(HDC hDC)
{
    for (UIElement* elem : _elements)
    {
        if (elem && elem->IsVisible())
        {
            elem->Render(hDC);
        }
    }
}

void SubUIManager::Add(UIElement* elem)
{
    if (!elem)
        return;

    uintptr_t ptr = reinterpret_cast<uintptr_t>(elem);
    if (ptr == 0xdddddddd || ptr == 0xfefefefe ||
        ptr == 0xffffffff || ptr == 0xffffffffffffffff || ptr < 0x10000)
    {
        std::cout << "[SubUIManager::Add] 잘못된 포인터 차단됨: 0x" << std::hex << ptr << std::endl;
        return;
    }

    _elements.push_back(elem);
}

void SubUIManager::Remove(UIElement* elem)
{
    if (elem)
    {
        _removeList.push_back(elem);
    }
}

void SubUIManager::Clear()
{
    for (UIElement*& elem : _elements)
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
    for (UIElement* elem : _removeList)
    {
        auto it = std::find(_elements.begin(), _elements.end(), elem);
        if (it != _elements.end())
        {
            if (*it)
            {
                delete* it;
                *it = nullptr;
            }

            _elements.erase(it);
        }
    }

    _removeList.clear();
}
