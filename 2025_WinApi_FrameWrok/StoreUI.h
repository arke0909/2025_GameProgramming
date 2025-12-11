#pragma once
#include "UIElement.h"
#include "UIButton.h"
#include "UILabel.h"
#include "ItemButton.h"

class Window;

class StoreUI : public UIElement
{
public:
    StoreUI(const Vec2& pos, const Vec2& size);
	~StoreUI();
    void SetWindowHandle(Window* storeWindow);
    void Update() override;
    void Render(HDC hdc) override;

private:
    void Init();
    void Reroll();
    std::vector<ItemInfo> GetRandomItems(int count);

private:
    std::vector<ItemButton*> _itemSlots;
    UIButton* _rerollButton = nullptr;
    UILabel* _coinLabel = nullptr;
    Window* _storeWindow = nullptr;
};
