#include "pch.h"
#include "StoreUI.h"
#include "GameManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameEvent.h"
#include <random>

extern std::vector<ItemInfo> AllItems;
extern std::unordered_set<ItemType> PurchasedItems;
extern std::unordered_map<ItemType, int> ItemPriceMap;

StoreUI::StoreUI(const Vec2& pos, const Vec2& size)
    : UIElement(pos, size)
{
    GameEvents::OnItemPurchased.Subscribe([this](const ItemInfo& info)
        {
            PurchasedItems.insert(info.type);
            ItemPriceMap[info.type] += static_cast<int>(info.value);
            Reroll();
        });

    Init();
}

void StoreUI::Init()
{
    _itemSlots.clear();
    auto items = GetRandomItems(3);

    for (int i = 0; i < (int)items.size(); ++i)
    {
        Vec2 slotPos = { pos.x - 160 + i * 160, pos.y - 50 };
        Vec2 slotSize = { 140, 200 };

        if (ItemPriceMap.count(items[i].type))
            items[i].price = ItemPriceMap[items[i].type];
        else
            ItemPriceMap[items[i].type] = items[i].price;

        auto* btn = new ItemButton(items[i], slotPos, slotSize);
        _itemSlots.push_back(btn);
    }

    Texture* buttonTex = GET_SINGLE(ResourceManager)->GetTexture(L"Button");
    _rerollButton = new UIButton(L"리롤", { pos.x + 170, pos.y + 130 }, { 100, 40 }, FontType::UI, buttonTex);
    _rerollButton->SetOnClick([this]() { Reroll(); });

    _coinLabel = new UILabel(L"Coin: 0", { pos.x + 150, pos.y + 70 }, { 200, 30 }, FontType::UI);
}

void StoreUI::Render(HDC hdc)
{
    if (!_visible) return;

    for (auto* btn : _itemSlots)
        btn->Render(hdc);

    _rerollButton->Render(hdc);

    std::wstring coinText = L"Coin: " + std::to_wstring(GET_SINGLE(GameManager)->coin);
    _coinLabel->SetText(coinText);
    _coinLabel->Render(hdc);
}

void StoreUI::Update()
{
    if (!_visible) return;

    for (auto* btn : _itemSlots)
        btn->Update();

    _rerollButton->Update();
}

void StoreUI::Reroll()
{
    const int cost = 50;

    if (!_itemSlots.empty() && GET_SINGLE(GameManager)->coin < cost)
    {
        MessageBox(nullptr, L"코인이 부족합니다!", L"리롤 실패", MB_OK);
        return;
    }

    if (!_itemSlots.empty())
        GET_SINGLE(GameManager)->coin -= cost;

    for (auto* btn : _itemSlots) delete btn;
    _itemSlots.clear();

    auto items = GetRandomItems(3);
    for (int i = 0; i < (int)items.size(); ++i)
    {
        Vec2 slotPos = { pos.x - 160 + i * 160, pos.y - 50 };
        Vec2 slotSize = { 140, 200 };

        if (ItemPriceMap.count(items[i].type))
            items[i].price = ItemPriceMap[items[i].type];

        auto* btn = new ItemButton(items[i], slotPos, slotSize);
        _itemSlots.push_back(btn);
    }
}

std::vector<ItemInfo> StoreUI::GetRandomItems(int count)
{
    std::vector<ItemInfo> candidates;

    for (const auto& item : AllItems)
    {
        if (PurchasedItems.count(item.type) == 0)
            candidates.push_back(item);
    }

    std::shuffle(candidates.begin(), candidates.end(), std::mt19937{ std::random_device{}() });

    if ((int)candidates.size() <= count)
        return candidates;

    return std::vector<ItemInfo>(candidates.begin(), candidates.begin() + count);
}
