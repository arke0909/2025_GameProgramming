#include "pch.h"
#include "UILabel.h"

UILabel::UILabel(const wstring& text, RECT rect, FontType fontType)
	: UIElement(rect), _text(text), _fontType(fontType) {
}

void UILabel::Render(HDC hdc)
{
	HFONT font = GET_SINGLE(ResourceManager)->GetFont(_fontType);
	if (!font)
		return;

	HFONT oldFont = (HFONT)::SelectObject(hdc, font);
	SetBkMode(hdc, TRANSPARENT);

	DrawText(hdc, _text.c_str(), -1, &_rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	::SelectObject(hdc, oldFont);
}
