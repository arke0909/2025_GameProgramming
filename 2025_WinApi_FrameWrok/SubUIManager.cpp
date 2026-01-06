#include "pch.h"
#include "SubUIManager.h"
#include "UIElement.h"

void SubUIManager::Update(HWND hWnd)
{

    for (size_t i = 0; i < _elements.size(); ++i)
    {
        UIElement* elem = _elements[i].get();
        if (!elem) continue;

        try
        {
            elem->Update();  
        }
        catch (...)
        {
            std::cerr << "[Error] elem->Update() exception\n";
        }
    }

    ProcessRemovals();
}

void SubUIManager::ProcessRemovals()
{
    if (_removeList.empty())
        return;

    _elements.erase(
        std::remove_if(
            _elements.begin(),
            _elements.end(),
            [&](const std::unique_ptr<UIElement>& elem)
            {
                return elem &&
                    std::find(_removeList.begin(), _removeList.end(), elem.get())
                    != _removeList.end();
            }),
        _elements.end()
    );

    _removeList.clear();
}

void SubUIManager::Render(HDC hDC)
{
    for (auto& elem : _elements)
    {
        if (elem && elem->IsVisible())
            elem->Render(hDC);
    }
}

void SubUIManager::Add(std::unique_ptr<UIElement> elem)
{
    if (elem)
        _elements.push_back(std::move(elem));
}

void SubUIManager::Remove(UIElement* elem)
{
    if (!elem) return;

    if (std::find(_removeList.begin(), _removeList.end(), elem) == _removeList.end())
        _removeList.push_back(elem);
}

void SubUIManager::Clear()
{
    _elements.clear();
    _removeList.clear();
}
