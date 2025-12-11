#pragma once
#include "pch.h"

class UIElement {
protected:
    Vec2 pos;
    Vec2 size;
    bool _visible = true;

public:
    UIElement(const Vec2& _pos, const Vec2& _size)
        : pos(_pos), size(_size) {
    }
    virtual ~UIElement() {}
    void SetVisible(bool v) { _visible = v; }
    bool IsVisible() const { return _visible; }

    virtual void Render(HDC hdc) = 0;
    virtual void Update() = 0;

    bool ContainsPoint(int x, int y) const {
        float left = pos.x - size.x / 2;
        float right = pos.x + size.x / 2;
        float top = pos.y - size.y / 2;
        float bottom = pos.y + size.y / 2;

        return x >= left && x <= right && y >= top && y <= bottom;
    }

    RECT GetRect() const {
        RECT r;
        r.left = (LONG)(pos.x - size.x / 2);
        r.right = (LONG)(pos.x + size.x / 2);
        r.top = (LONG)(pos.y - size.y / 2);
        r.bottom = (LONG)(pos.y + size.y / 2);
        return r;
    }
};
