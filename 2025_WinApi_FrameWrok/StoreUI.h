#pragma once
#include "UIElement.h"
#include "ItemButton.h"
#include "UILabel.h"
#include "UIButton.h"

class StoreUI : public UIElement
{
public:
    StoreUI(const Vec2& pos, const Vec2& size);

    void Render(HDC hdc) override;
    void Update() override;

private:
    void Init();
    void Reroll();
    std::vector<ItemInfo> GetRandomItems(int count);

    std::vector<ItemButton*> _itemSlots;
    UIButton* _rerollButton = nullptr;
    UILabel* _coinLabel = nullptr;
};
