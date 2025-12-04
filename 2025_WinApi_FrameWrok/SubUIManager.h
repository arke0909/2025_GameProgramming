#pragma once
#include "UIElement.h"

class SubUIManager
{
public:
    void Add(UIElement* elem);
    void Update(HWND hWnd);
    void Render(HDC hdc);
    int Count();
    void Clear();

private:
    std::vector<UIElement*> _elements;
};
