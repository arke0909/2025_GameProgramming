#pragma once
#include "UILabel.h"

class CoinLabel : public UILabel
{
public:
    CoinLabel(const Vec2& pos, const Vec2& size, FontType fontType);

    virtual void Update() override;

};

