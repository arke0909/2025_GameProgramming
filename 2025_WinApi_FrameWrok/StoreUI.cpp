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

    Texture* buttonTex = GET_SINGLE(ResourceManager)->GetTexture(L"Button");
    _rerollButton = new UIButton(L"리롤", { pos.x + 170, pos.y + 130 }, { 100, 40 }, FontType::UI, buttonTex);

    _rerollButton->SetOnClick([this]()
        {
            Reroll();
        });

    _coinLabel = new UILabel(L"Coin: 0", Vec2(pos.x + 150, pos.y + 70), Vec2(200, 30), FontType::UI);
}


void StoreUI::Render(HDC hdc)
{
    if (!_visible) return;

    for (auto* btn : _itemSlots)
        btn->Render(hdc);

    if (_rerollButton)
        _rerollButton->Render(hdc);

    if (_coinLabel)
    {
        std::wstring coinText = L"Coin: " + std::to_wstring(GET_SINGLE(GameManager)->coin);
        _coinLabel->SetText(coinText);
        _coinLabel->Render(hdc);
    }
}


void StoreUI::Update()
{
    if (!_visible) return;

    for (auto* btn : _itemSlots)
        btn->Update();

    if (_rerollButton)
        _rerollButton->Update();
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

    auto items = GetRandomItems(3);
    for (int i = 0; i < 3; ++i)
    {
        Vec2 slotPos = { pos.x - 160 + i * 160, pos.y - 50 };
        Vec2 slotSize = { 140, 200 };

        auto* btn = new ItemButton(items[i], slotPos, slotSize);
        _itemSlots.push_back(btn);
    }
}


std::vector<ItemInfo> StoreUI::GetRandomItems(int count)
{
    std::vector<ItemInfo> shuffled = AllItems;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(shuffled.begin(), shuffled.end(), g);

    return std::vector<ItemInfo>(shuffled.begin(), shuffled.begin() + count);
}
