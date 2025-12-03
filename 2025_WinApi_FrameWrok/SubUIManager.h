#pragma once
#include "UIElement.h"

class SubUIManager
{
public:
    void Add(UIElement* elem);
    void Update(HWND hWnd);
    void Render(HDC hdc);
    void Clear();

private:
    std::vector<UIElement*> _elements;
};
