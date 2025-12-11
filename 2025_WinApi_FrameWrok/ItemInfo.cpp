#include "pch.h"
#include "ItemInfo.h"

std::vector<ItemInfo> AllItems = {
    { ItemType::PlayerSpeed,    L"이속",         STAT_SPEED,    L"플레이어의 속도를 증가시킵니다.",     100, 75,    nullptr },
    { ItemType::WeaponSpeed,    L"무기 속도",         STAT_WEAPONSPEED, L"무기의 속도를 증가시킵니다.",     100, 100,    nullptr },
    { ItemType::WallPunch,      L"월펀치",       STAT_WALLFORCE, L"벽 밀림 강도를 증가시킵니다.",       80,  10,    nullptr },
    { ItemType::MoneyDrop,      L"재력",         STAT_GOLDMULTI, L"드랍되는 돈이 증가합니다.",          90,  0.5f,  nullptr },
    { ItemType::MaxHealth,      L"최대 체력",    STAT_HP, L"최대 체력이 5 증가합니다.",         150, 5,     nullptr },
    { ItemType::Heal20HP,       L"20HP 회복",    HEAL ,L"체력을 20 회복합니다.",             350,  20,    nullptr },
    { ItemType::WeaponSize,      L"무기 크기 증가", STAT_WEAPON_SIZE,L"무기의 사이즈가 증가합니다.",  130, 5,     nullptr },
    { ItemType::SplashDamage,   L"스플래쉬",     STAT_SPLASH,   L"범위 공격 효과가 추가됩니다.",       140, 1,     nullptr },
};

std::unordered_map<ItemType, int> PriceIncreaseMap = {
    { ItemType::PlayerSpeed, 50 },
    { ItemType::WeaponSpeed, 50 },
    { ItemType::WallPunch, 50 },
    { ItemType::MoneyDrop, 50 },
    { ItemType::MaxHealth, 50 },
    { ItemType::Heal20HP, 0 },
    { ItemType::WeaponSize, 50 },
    { ItemType::SplashDamage, 250 },
    { ItemType::Pierce, 50 },
};
std::unordered_set<ItemType> PurchasedItems;
std::unordered_map<ItemType, int> ItemPriceMap;
