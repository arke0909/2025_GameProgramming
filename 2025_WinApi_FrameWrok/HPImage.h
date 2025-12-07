#pragma once
#include "UIImage.h"

class HPImage : public UIImage
{
public:
    HPImage(const Vec2& pos, const Vec2& size, Texture* texture)
        : UIImage(texture, pos, size) {
    }

    void Update() override;
};
