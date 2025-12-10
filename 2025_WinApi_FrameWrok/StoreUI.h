#pragma once
#include "UIElement.h"
#include "UIButton.h"
#include "UILabel.h"
#include "Window.h"
#include "ItemButton.h"

class StoreUI : public UIElement
{
public:
    StoreUI(const Vec2& pos, const Vec2& size);
    void SetWindowHandle(Window* storeWindow);
    void Init();
    void Update() override;
    void Render(HDC hdc) override;

private:
    void Reroll();
    std::vector<ItemInfo> GetRandomItems(int count);

    std::vector<ItemButton*> _itemSlots;
    UIButton* _rerollButton = nullptr;
    UILabel* _coinLabel = nullptr;
    bool _storeVisible = true;
    Window* _storeWindow;
};
