#include "pch.h"
#include "UIButton.h"
#include "InputManager.h"
#include "ResourceManager.h"


UIButton::UIButton(const wstring& text, RECT rect, FontType fontType, Texture* texture)
	: UIElement(rect), _text(text), _fontType(fontType), _texture(texture)
{
}

void UIButton::Render(HDC hdc)
{

    if (!_texture || !_texture->GetTextureDC()) return;

    BitBlt(hdc, _rect.left, _rect.top,
        _rect.right - _rect.left, _rect.bottom - _rect.top,
        _texture->GetTextureDC(), 0, 0, SRCCOPY);

    HFONT font = GET_SINGLE(ResourceManager)->GetFont(_fontType);
    if (!font)
        return;

    HFONT oldFont = (HFONT)::SelectObject(hdc, font);
    SetBkMode(hdc, TRANSPARENT);

    DrawText(hdc, _text.c_str(), -1, &_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    ::SelectObject(hdc, oldFont);
}

void UIButton::Update() {
    const POINT& pos = GET_SINGLE(InputManager)->GetMousePos();

    if (ContainsPoint(pos.x, pos.y)) {
        if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::LBUTTON)) {
            if (_onClick)
                _onClick();
        }
    }
}
