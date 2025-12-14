#include "pch.h"
#include "StoreUI.h"
#include "GameManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameEvent.h"
#include "ItemButton.h"
#include "UILabel.h"
#include "UIButton.h"
#include <random>
#include <unordered_set>

StoreUI::StoreUI(const Vec2& pos, const Vec2& size) : UIElement(pos, size)
{
    GameEvents::OnItemPurchased.Subscribe([this](const ItemInfo& item) {
        Reroll(false);
        });

    Init();
}

StoreUI::~StoreUI() {
    for (auto* btn : _itemSlots) delete btn;
    delete _rerollButton;
    delete _coinLabel;
}

void StoreUI::Init() {
    auto items = GetRandomItems(3);
    InitWithItems(items);
}

void StoreUI::InitWithItems(const std::vector<ItemInfo>& items) {
    _currentItems = items;

    for (auto*& btn : _itemSlots) {
        delete btn;
        btn = nullptr;
    }
    _itemSlots.clear();

    for (int i = 0; i < 3; ++i) {
        if (i >= items.size()) {
            _itemSlots.push_back(nullptr);
            continue;
        }

        Vec2 slotPos = { pos.x - 160 + i * 160, pos.y - 50 };
        Vec2 slotSize = { 140, 200 };

        auto* btn = new ItemButton(items[i], slotPos, slotSize);
        _itemSlots.push_back(btn);
    }

    auto tex = GET_SINGLE(ResourceManager)->GetTexture(L"Button");
    _rerollButton = new UIButton(L"¸®·Ñ 50", { pos.x + 170, pos.y + 130 }, { 100, 40 }, FontType::UI, tex);
    _rerollButton->SetOnClick([this]() { Reroll(true); });

    _coinLabel = new UILabel(L"Coin: 0", Vec2(pos.x + 150, pos.y + 70), Vec2(200, 30), FontType::UI);
}

void StoreUI::Reroll(bool charge) {
    const int cost = 50;
    if (charge && GET_SINGLE(GameManager)->coin < cost) return;

    if (charge) {
        GET_SINGLE(GameManager)->coin -= cost;
        GET_SINGLE(ResourceManager)->Play(L"ReRollSound");
    }

    for (auto*& btn : _itemSlots) {
        delete btn;
        btn = nullptr;
    }
    _itemSlots.clear();

    auto items = GetRandomItems(3);
    InitWithItems(items);
}

std::vector<ItemInfo> StoreUI::GetRandomItems(int count) {
    std::vector<ItemInfo> candidates = AllItems;
    std::shuffle(candidates.begin(), candidates.end(), std::mt19937{ std::random_device{}() });

    std::unordered_set<ItemType> selected;
    std::vector<ItemInfo> result;

    for (auto item : candidates) {
        if ((int)item.type < 0 || (int)item.type >= (int)ItemType::COUNT) continue;
        if (selected.count(item.type)) continue;

        selected.insert(item.type);

        if (ItemPriceMap.contains(item.type)) {
            item.price = ItemPriceMap[item.type];
        }

        result.push_back(item);
        if ((int)result.size() >= count) break;
    }

    return result;
}

void StoreUI::Update() {
    if (!_visible) return;
    for (auto* btn : _itemSlots) if (btn) btn->Update();
    if (_rerollButton) _rerollButton->Update();
}

void StoreUI::Render(HDC hdc) {
    if (!_visible) return;
    for (auto* btn : _itemSlots) if (btn) btn->Render(hdc);
    if (_rerollButton) _rerollButton->Render(hdc);

    std::wstring coinText = L"Coin: " + std::to_wstring(GET_SINGLE(GameManager)->coin);
    _coinLabel->SetText(coinText);
    _coinLabel->Render(hdc);
}
