#pragma once
#include "UILabel.h"

class WaveLabel : public UILabel
{
public:
    WaveLabel(const Vec2& pos, const Vec2& size, FontType fontType);

    virtual void Update() override;
};

