#pragma once
#include "UIElement.h"

class UILabel : public UIElement
{
private:
    wstring _text;
    FontType _fontType;

public:
    UILabel(const wstring& text, const Vec2& pos, const Vec2& size, FontType fontType);

    void Render(HDC hdc) override;
    void Update() override {}
};
