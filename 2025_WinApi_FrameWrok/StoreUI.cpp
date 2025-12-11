#include "pch.h"
#include "StoreUI.h"
#include "GameManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameEvent.h"
#include "Window.h"
#include <random>
#include <unordered_set>

extern std::vector<ItemInfo> AllItems;
extern std::unordered_map<ItemType, int> ItemPriceMap;
extern std::unordered_map<ItemType, int> PriceIncreaseMap;

StoreUI::StoreUI(const Vec2& pos, const Vec2& size)
    : UIElement(pos, size)
{
    GameEvents::OnItemPurchased.Subscribe([this](const ItemInfo& item)
        {
            Reroll(false);
        });

    Init();
}

StoreUI::~StoreUI()
{
    for (auto* btn : _itemSlots)
        delete btn;
    _itemSlots.clear();

    delete _rerollButton;
    delete _coinLabel;
}

void StoreUI::SetWindowHandle(Window* storeWindow)
{
    _storeWindow = storeWindow;
}

void StoreUI::Init()
{
    auto items = GetRandomItems(3);
    InitWithItems(items);
}

void StoreUI::InitWithItems(const std::vector<ItemInfo>& items)
{
    _currentItems = items;

    for (auto*& btn : _itemSlots)
    {
        delete btn;
        btn = nullptr;
    }
    _itemSlots.clear();

    for (int i = 0; i < 3; ++i)
    {
        Vec2 slotPos = { pos.x - 160 + i * 160, pos.y - 50 };
        Vec2 slotSize = { 140, 200 };

        if (i >= (int)items.size())
        {
            _itemSlots.push_back(nullptr);
            continue;
        }

        const auto& item = items[i];
        auto* btn = new ItemButton(item, slotPos, slotSize);
        _itemSlots.push_back(btn);
    }

    auto tex = GET_SINGLE(ResourceManager)->GetTexture(L"Button");
    _rerollButton = new UIButton(L"¸®·Ñ 50", { pos.x + 170, pos.y + 130 }, { 100, 40 }, FontType::UI, tex);
    _rerollButton->SetOnClick([this]() { Reroll(true); });

    _coinLabel = new UILabel(L"Coin: 0", Vec2(pos.x + 150, pos.y + 70), Vec2(200, 30), FontType::UI);
}

void StoreUI::Update()
{
    if (!_visible) return;

    for (auto* btn : _itemSlots)
        if (btn) btn->Update();

    if (_rerollButton)
        _rerollButton->Update();
}

void StoreUI::Render(HDC hdc)
{
    if (!_visible) return;

    for (auto* btn : _itemSlots)
        if (btn) btn->Render(hdc);

    if (_rerollButton)
        _rerollButton->Render(hdc);

    if (_coinLabel)
    {
        std::wstring coinText = L"Coin: " + std::to_wstring(GET_SINGLE(GameManager)->coin);
        _coinLabel->SetText(coinText);
        _coinLabel->Render(hdc);
    }
}

void StoreUI::Reroll(bool charge)
{
    const int cost = 50;

    if (charge && !_itemSlots.empty() && GET_SINGLE(GameManager)->coin < cost)
    {
        return;
    }

    if (charge)
    {
        GET_SINGLE(GameManager)->coin -= cost;
        GET_SINGLE(ResourceManager)->Play(L"ReRollSound");
    }

    for (auto*& btn : _itemSlots)
    {
        delete btn;
        btn = nullptr;
    }
    _itemSlots.clear();

    auto rerolledItems = GetRandomItems(3);
    InitWithItems(rerolledItems);
}

std::vector<ItemInfo> StoreUI::GetRandomItems(int count)
{
    std::vector<ItemInfo> candidates = AllItems;
    std::shuffle(candidates.begin(), candidates.end(), std::mt19937{ std::random_device{}() });

    std::unordered_set<ItemType> selected;
    std::vector<ItemInfo> result;

    for (auto& item : candidates)
    {
        if (selected.count(item.type)) continue;
        selected.insert(item.type);

        if (ItemPriceMap.count(item.type))
            item.price = ItemPriceMap[item.type];

        result.push_back(item);

        if ((int)result.size() >= count)
            break;
    }

    return result;
}

const std::vector<ItemInfo>& StoreUI::GetCurrentItems() const
{
    return _currentItems;
}
