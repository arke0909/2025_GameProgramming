#pragma once
#include "UIElement.h"
#include "ItemInfo.h"
#include <functional>

class UIImage;
class UILabel;

class ItemButton : public UIElement
{
public:
    ItemButton(const ItemInfo& info, const Vec2& pos, const Vec2& size);
    ~ItemButton();

    void Render(HDC hdc) override;
    void Update() override;
    bool IsClicked(POINT pt) const;
    void OnClick();

private:
    ItemInfo _info;
    UIImage* _background;
    UILabel* _nameLabel;
    UILabel* _descLabel;
    UILabel* _priceLabel;

    std::function<void()> _onClick;
    bool ContainsPoint(int x, int y) const;
};
