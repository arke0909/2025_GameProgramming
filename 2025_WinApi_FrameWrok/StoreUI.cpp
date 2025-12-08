#include "pch.h"
#include "StoreUI.h"
#include "GameManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include <algorithm>
#include <random>

extern std::vector<ItemInfo> AllItems;

StoreUI::StoreUI(const Vec2& pos, const Vec2& size)
    : UIElement(pos, size)
{
    Init();
}

void StoreUI::Init()
{
    _itemSlots.clear();
    auto items = GetRandomItems(3);

    for (int i = 0; i < 3; ++i)
    {
        Vec2 slotPos = { pos.x - 160 + i * 160, pos.y - 50 };
        Vec2 slotSize = { 140, 200 };

        auto* btn = new ItemButton(items[i], slotPos, slotSize);
        _itemSlots.push_back(btn);
    }

    _rerollRect = { (LONG)(pos.x + 120), (LONG)(pos.y + 110), (LONG)(pos.x + 220), (LONG)(pos.y + 150) };
}

void StoreUI::Render(HDC hdc)
{
    if (!_visible) return;

    for (auto* btn : _itemSlots)
        btn->Render(hdc);

    FillRect(hdc, &_rerollRect, (HBRUSH)(COLOR_WINDOW + 1));
    DrawText(hdc, L"리롤", -1, &_rerollRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    std::wstring coinText = L"Coin: " + std::to_wstring(GET_SINGLE(GameManager)->coin);
    RECT coinRect = { _rerollRect.left, _rerollRect.top - 40, _rerollRect.right + 100, _rerollRect.top };
    DrawText(hdc, coinText.c_str(), -1, &coinRect, DT_LEFT);
}

void StoreUI::Update()
{
    if (!_visible) return;

    POINT mousePos = GET_SINGLE(InputManager)->GetMousePosClient();

    if (PtInRect(&_rerollRect, mousePos))
    {
        if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::LBUTTON))
        {
            Reroll();
        }
    }

    for (auto* btn : _itemSlots)
        btn->Update();
}

void StoreUI::Reroll()
{
    const int cost = 50;
    if (GET_SINGLE(GameManager)->coin < cost)
    {
        MessageBox(nullptr, L"코인이 부족합니다!", L"리롤 실패", MB_OK);
        return;
    }

    GET_SINGLE(GameManager)->coin -= cost;

    for (auto* btn : _itemSlots)
        delete btn;

    _itemSlots.clear();
    Init();
}

std::vector<ItemInfo> StoreUI::GetRandomItems(int count)
{
    std::vector<ItemInfo> shuffled = AllItems;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffled.begin(), shuffled.end(), g);

    return std::vector<ItemInfo>(shuffled.begin(), shuffled.begin() + count);
}
