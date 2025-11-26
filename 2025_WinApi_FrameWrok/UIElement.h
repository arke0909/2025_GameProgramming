#pragma once
#include "pch.h"

class UIElement {
protected:
    RECT _rect;
    bool _visible = true;

public:
    UIElement(RECT rect) : _rect(rect) {}
    virtual ~UIElement() = default;
    virtual void Update() = 0;

    virtual void Render(HDC hdc) = 0;

    RECT GetRect() const { return _rect; }
    void SetVisible(bool visible) { _visible = visible; }
    bool IsVisible() const { return _visible; }

    bool ContainsPoint(int x, int y) const 
    {
        return PtInRect(&_rect, POINT{ x, y });
    }
};
