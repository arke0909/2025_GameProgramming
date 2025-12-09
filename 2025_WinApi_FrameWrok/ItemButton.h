#pragma once
#include "UIElement.h"
#include "ItemInfo.h"

class ItemButton : public UIElement
{
public:
    ItemButton(const ItemInfo& info, const Vec2& pos, const Vec2& size);

    void Render(HDC hdc) override;
    void Update() override;

    bool IsClicked(POINT pt) const;
    void OnClick();

    const ItemInfo& GetInfo() const { return _info; }

private:
    ItemInfo _info;
    std::function<void()> _onClick;
};
