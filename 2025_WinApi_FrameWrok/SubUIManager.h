#pragma once
#include "UIElement.h"

class SubUIManager
{
public:
    void Update(HWND hWnd);
    void Render(HDC hDC);

    void Add(UIElement* elem);
    void Remove(UIElement* elem);
    void Clear();

    void ProcessRemovals();

    size_t Count() const { return _elements.size(); }

private:
    std::vector<UIElement*> _elements;
    std::vector<UIElement*> _removeList;
};