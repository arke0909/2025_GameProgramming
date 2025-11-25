#pragma once
#include "UIElement.h"
#include "ResourceManager.h"

class UILabel : public UIElement
{
private:
	wstring _text;
	FontType _fontType;

public:
	UILabel(const wstring& text, RECT rect, FontType fontType);

	virtual void Render(HDC hdc) override;
};
