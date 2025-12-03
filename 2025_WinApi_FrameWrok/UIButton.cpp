#include "pch.h"
#include "UIButton.h"
#include "InputManager.h"
#include "ResourceManager.h"

UIButton::UIButton(const std::wstring& text, const Vec2& pos, const Vec2& size, FontType fontType, Texture* texture)
    : UIElement(pos, size), _text(text), _fontType(fontType), _texture(texture)
{
}

void UIButton::Render(HDC hdc)
{
    if (!_texture || !_texture->GetTextureDC()) return;

    RECT rc = GetRect();

    ::TransparentBlt(hdc,
        rc.left, rc.top,
        rc.right - rc.left,
        rc.bottom - rc.top,
        _texture->GetTextureDC(),
        0, 0,
        _texture->GetWidth(),
        _texture->GetHeight(),
        RGB(255, 0, 255));

    HFONT font = GET_SINGLE(ResourceManager)->GetFont(_fontType);
    if (!font) return;

    HFONT oldFont = (HFONT)::SelectObject(hdc, font);
    SetBkMode(hdc, TRANSPARENT);

    DrawText(hdc, _text.c_str(), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    ::SelectObject(hdc, oldFont);
}


void UIButton::Update() {
    const POINT& pos = GET_SINGLE(InputManager)->GetMousePos();

    if (ContainsPoint(pos.x, pos.y)) 
    {
        if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::LBUTTON)) {
            if (_onClick)
                _onClick();
        }
    }
}
