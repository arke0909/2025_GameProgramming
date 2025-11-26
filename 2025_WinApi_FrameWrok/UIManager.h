#pragma once
#include "UIElement.h"
class UIManager
{
DECLARE_SINGLE(UIManager);
public:
	void Add(UIElement* elem);
	void Render(HDC hdc);
	void Update();
	void HandleInput(UINT msg, WPARAM wParam, LPARAM lParam);
	void Clear();
private:
	std::vector<UIElement*> _elements;
};

