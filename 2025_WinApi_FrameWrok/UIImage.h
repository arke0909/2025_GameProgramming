#pragma once
#include "UIElement.h"

class Texture;
class UIImage : public UIElement {
public:
    UIImage(Texture* texture, const Vec2& pos, const Vec2& size);
    ~UIImage() override = default;
    void Render(HDC hdc) override;
	void Update() override {}

private:
    Texture* _texture = nullptr;
};
