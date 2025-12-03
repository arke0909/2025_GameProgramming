#pragma once
#include "UIElement.h"

class Texture;
class UIButton : public UIElement {
private:
    std::function<void()> _onClick;	
    wstring _text;
    FontType _fontType;
    Texture* _texture = nullptr;

public:
    UIButton(const std::wstring& text, const Vec2& pos, const Vec2& size, FontType fontType, Texture* texture);

    void SetFont(FontType type) { _fontType = type; };
    void SetOnClick(std::function<void()> cb) { _onClick = cb; }

    void Render(HDC hdc) override;
    void Update() override;
};
