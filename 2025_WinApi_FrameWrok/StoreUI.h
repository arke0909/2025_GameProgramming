#pragma once
#include "UIElement.h"
#include "ItemButton.h"
#include "ItemInfo.h"

class StoreUI : public UIElement
{
public:
    StoreUI(const Vec2& pos, const Vec2& size);

    void Init();
    void Render(HDC hdc) override;
    void Update() override;

private:
    std::vector<ItemButton*> _itemSlots;
    UIElement* _rerollButton;
    RECT _rerollRect;

    void Reroll();
    std::vector<ItemInfo> GetRandomItems(int count);
};
