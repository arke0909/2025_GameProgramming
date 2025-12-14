#pragma once
#include "UIElement.h"
#include "ItemInfo.h"

class ItemButton;
class UIButton;
class UILabel;

class StoreUI : public UIElement {
public:
    StoreUI(const Vec2& pos, const Vec2& size);
    virtual ~StoreUI();

    void Update() override;
    void Render(HDC hdc) override;

private:
    void Init();
    void InitWithItems(const std::vector<ItemInfo>& items);
    std::vector<ItemInfo> GetRandomItems(int count);
    void Reroll(bool charge);

private:
    std::vector<ItemButton*> _itemSlots;
    std::vector<ItemInfo> _currentItems;
    UIButton* _rerollButton = nullptr;
    UILabel* _coinLabel = nullptr;
};
