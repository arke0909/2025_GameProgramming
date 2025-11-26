#pragma once
#include "UIElement.h"
class UIManager
{
DECLARE_SINGLE(UIManager);
public:
	void Add(UIElement* elem);
	void Render(HDC hdc);
	void Update();
	void Clear();
private:
	std::vector<UIElement*> _elements;
};

