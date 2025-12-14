#include "pch.h"
#include "ItemInfo.h"

std::vector<ItemInfo> AllItems = {
    { ItemType::PlayerSpeed,    L"이속",         L"속도",    L"플레이어 속도 증가", 100, 75, nullptr },
    { ItemType::WeaponSpeed,    L"무기 속도",    L"속도",    L"무기 속도 증가",     100, 100, nullptr },
    { ItemType::WallPunch,      L"월펀치",       L"강도",    L"벽 밀기 강도 증가",  80, 10, nullptr },
    { ItemType::MoneyDrop,      L"재력",         L"드랍",    L"드랍 금 증가",       90, 0.5f, nullptr },
    { ItemType::MaxHealth,      L"최대 체력",    L"체력",    L"체력 +5",           150, 5, nullptr },
    { ItemType::Heal20HP,       L"HP 회복",      L"회복",    L"체력 회복",         110, 1, nullptr },
    { ItemType::WeaponSize,     L"무기 크기",     L"크기",    L"무기 크기 증가",     130, 5, nullptr },
    { ItemType::SplashDamage,   L"스플래쉬",     L"범위",    L"범위 데미지 추가",   140, 1, nullptr },
};

std::unordered_map<ItemType, int> PriceIncreaseMap = {
    { ItemType::PlayerSpeed, 50 },
    { ItemType::WeaponSpeed, 50 },
    { ItemType::WallPunch, 50 },
    { ItemType::MoneyDrop, 50 },
    { ItemType::MaxHealth, 50 },
    { ItemType::Heal20HP, 50 },
    { ItemType::WeaponSize, 50 },
    { ItemType::SplashDamage, 250 },
    { ItemType::Pierce, 50 },
};

std::unordered_map<ItemType, int> ItemPriceMap;
std::unordered_set<ItemType> PurchasedItems;
