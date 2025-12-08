#include "pch.h"
#include "ItemButton.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "InputManager.h"

ItemButton::ItemButton(const ItemInfo& info, const Vec2& pos, const Vec2& size)
    : UIElement(pos, size), _info(info)
{
    _onClick = [this]() {
        if (GET_SINGLE(GameManager)->coin >= _info.price)
        {
            GET_SINGLE(GameManager)->coin -= _info.price;
            MessageBox(nullptr, (_info.name + L" 구매 완료!").c_str(), L"구매", MB_OK);
        }
        else
        {
            MessageBox(nullptr, L"코인이 부족합니다!", L"실패", MB_OK);
        }
        };
}

void ItemButton::Render(HDC hdc)
{
    if (!_visible) return;

    RECT rc = GetRect();
    FillRect(hdc, &rc, (HBRUSH)(COLOR_WINDOW + 2));

    HFONT font = GET_SINGLE(ResourceManager)->GetFont(FontType::TITLE);
    HFONT oldFont = (HFONT)SelectObject(hdc, font);
    SetBkMode(hdc, TRANSPARENT);

    DrawText(hdc, _info.name.c_str(), -1, &rc, DT_CENTER | DT_TOP);
    DrawText(hdc, _info.description.c_str(), -1, &rc, DT_CENTER | DT_VCENTER);

    RECT priceRect = rc;
    priceRect.top += 140;

    std::wstring priceText = L"가격: " + std::to_wstring(_info.price);
    DrawText(hdc, priceText.c_str(), -1, &priceRect, DT_CENTER | DT_TOP);

    SelectObject(hdc, oldFont);
}

void ItemButton::Update()
{
    if (!_visible) return;

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

void ItemButton::OnClick()
{
    if (_onClick)
        _onClick();
}
