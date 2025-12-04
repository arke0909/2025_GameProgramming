#include "pch.h"
#include "UILabel.h"
#include "ResourceManager.h"

UILabel::UILabel(const wstring& text, const Vec2& pos, const Vec2& size, FontType fontType)
    : UIElement(pos, size), _text(text), _fontType(fontType)
{
}

void UILabel::SetColor(COLORREF color)
{
    _color = color;
}

void UILabel::Render(HDC hdc)
{
    HFONT font = GET_SINGLE(ResourceManager)->GetFont(_fontType);
    if (!font)
        return;

    HFONT oldFont = (HFONT)::SelectObject(hdc, font);

    ::SetBkMode(hdc, TRANSPARENT);
    ::SetTextColor(hdc, _color);

    RECT rc = GetRect();
    DrawTextW(hdc, _text.c_str(), -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    ::SelectObject(hdc, oldFont);
}
