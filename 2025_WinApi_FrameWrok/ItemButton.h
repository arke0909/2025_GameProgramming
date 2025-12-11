#pragma once
#include "UIElement.h"
#include "ItemInfo.h"

class UIImage;
class UILabel;

class ItemButton : public UIElement
{
public:
    ItemButton(const ItemInfo& info, const Vec2& pos, const Vec2& size);
    ~ItemButton();

    void Update() override;
    void Render(HDC hdc) override;
    void OnClick();

private:
    bool ContainsPoint(int x, int y) const;

private:
    ItemInfo _info;
    std::function<void()> _onClick;
    UIImage* _background = nullptr;
    UILabel* _nameLabel = nullptr;
    UILabel* _descLabel = nullptr;
    UILabel* _priceLabel = nullptr;
};
