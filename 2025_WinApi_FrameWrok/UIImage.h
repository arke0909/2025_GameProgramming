#pragma once
#include "UIElement.h"

class Texture;
class UIImage : public UIElement {
public:
    UIImage(Texture* texture, RECT rect);

    void Render(HDC hdc) override;
    void HandleInput(UINT, WPARAM, LPARAM) override {}

private:
    Texture* _texture = nullptr;
};
