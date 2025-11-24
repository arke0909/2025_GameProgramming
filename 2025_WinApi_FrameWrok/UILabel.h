#pragma once
#include "UIElement.h"

class UILabel : public UIElement
{
private:
	wstring _text;

public:
	UILabel(const wstring& text, RECT rect);
};

