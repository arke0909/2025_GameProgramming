#include "pch.h"
#include "ItemButton.h"
#include "UIImage.h"
#include "UILabel.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Texture.h"
#include "GameEvent.h"

ItemButton::ItemButton(const ItemInfo& info, const Vec2& pos, const Vec2& size)
    : UIElement(pos, size), _info(info)
{
    Texture* tex = GET_SINGLE(ResourceManager)->GetTexture(L"SkillPanel");

    _background = new UIImage(tex, pos, size);

    _nameLabel = new UILabel(
        _info.name,
        Vec2(pos.x, pos.y - 60),
        Vec2(size.x, 30.0f),
        FontType::UI
    );

    _descLabel = new UILabel(
        _info.description,
        Vec2(pos.x, pos.y),
        Vec2(size.x, 60.0f),
        FontType::UI
    );

    _priceLabel = new UILabel(
        L"가격: " + std::to_wstring(_info.price),
        Vec2(pos.x, pos.y + 60),
        Vec2(size.x, 30.0f),
        FontType::UI
    );

    _onClick = [this]()
        {
            if (GET_SINGLE(GameManager)->coin >= _info.price)
            {
                GET_SINGLE(GameManager)->coin -= _info.price;
                GameEvents::OnItemPurchased.Raise(_info.type);
            }
            else
            {
                MessageBox(nullptr, L"코인이 부족합니다!", L"구매 실패", MB_OK);
            }
        };
}

ItemButton::~ItemButton()
{
    delete _background;
    delete _nameLabel;
    delete _descLabel;
    delete _priceLabel;
}

void ItemButton::Render(HDC hdc)
{
    if (!_visible) return;

    _background->Render(hdc);
    _nameLabel->Render(hdc);
    _descLabel->Render(hdc);
    _priceLabel->Render(hdc);
}

void ItemButton::Update()
{
    if (!_visible) return;

    HWND currentFocus = ::GetFocus();
    HWND storeWindow = GET_SINGLE(GameManager)->storeWindowHandle;

    if (currentFocus != storeWindow)
        return;

    const POINT& mousePos = GET_SINGLE(InputManager)->GetMousePosClient();
    if (ContainsPoint(mousePos.x, mousePos.y))
    {
        if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::LBUTTON))
        {
            OnClick();
        }
    }
}

bool ItemButton::IsClicked(POINT pt) const
{
    return ContainsPoint(pt.x, pt.y);
}

bool ItemButton::ContainsPoint(int x, int y) const
{
    float left = pos.x - size.x / 2;
    float right = pos.x + size.x / 2;
    float top = pos.y - size.y / 2;
    float bottom = pos.y + size.y / 2;

    return x >= left && x <= right && y >= top && y <= bottom;
}

void ItemButton::OnClick()
{
    if (_onClick)
        _onClick();
}
