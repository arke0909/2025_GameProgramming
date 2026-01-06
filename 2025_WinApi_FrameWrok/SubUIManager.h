#pragma once
#include "UIElement.h"

class SubUIManager
{
public:
    void Update(HWND hWnd);
    void Render(HDC hDC);

    void Add(std::unique_ptr<UIElement> elem);
    void Remove(UIElement* elem);
    void Clear();

    size_t Count() const { return _elements.size(); }

private:
    void ProcessRemovals();

private:
    std::vector<std::unique_ptr<UIElement>> _elements;
    std::vector<UIElement*> _removeList;
};
