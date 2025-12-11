#pragma once
#include "UIElement.h"
#include "ItemButton.h"
#include "UIButton.h"
#include "UILabel.h"
#include "ItemInfo.h"
#include "Window.h"

class StoreUI : public UIElement
{
public:
    StoreUI(const Vec2& pos, const Vec2& size);
    virtual ~StoreUI();

    void SetWindowHandle(Window* storeWindow);
    void Update() override;
    void Render(HDC hdc) override;

    void Reroll(bool charge = true); 
    const std::vector<ItemInfo>& GetCurrentItems() const;

private:
    void Init(); 
    void InitWithItems(const std::vector<ItemInfo>& items); 
    std::vector<ItemInfo> GetRandomItems(int count);

private:
    Window* _storeWindow = nullptr;
    std::vector<ItemButton*> _itemSlots;
    UIButton* _rerollButton = nullptr;
    UILabel* _coinLabel = nullptr;

    std::vector<ItemInfo> _currentItems;
};
