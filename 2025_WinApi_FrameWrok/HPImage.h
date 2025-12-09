#pragma once
#include "UILabel.h"

class HpLabel : public UILabel
{
public:
    HpLabel(const Vec2& pos, const Vec2& size, FontType fontType);
    void Update() override;
};
