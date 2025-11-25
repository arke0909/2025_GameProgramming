#pragma once
#include "UIElement.h"

class Texture;
class UIImage : public UIElement {
public:
    UIImage(Texture* texture, RECT rect);
    void Render(HDC hdc) override;
	void Update() override {}

private:
    Texture* _texture = nullptr;
};
