#include "pch.h"
#include "ItemInfo.h"

std::vector<ItemInfo> AllItems = {
    { ItemType::PlayerSpeed,    L"이속",         L"PlayerSpeed",    L"플레이어의 속도를 증가시킵니다.",     100, 75,    nullptr },
    { ItemType::AttackSpeed,    L"공속",         L"AttackSpeed",    L"공격 속도를 증가시킵니다.",         120, -0.15f, nullptr },
    { ItemType::WallPunch,      L"월펀치",       L"WallPunch",      L"벽 밀림 강도를 증가시킵니다.",       80,  10,    nullptr },
    { ItemType::MoneyDrop,      L"재력",         L"MoneyDrop",      L"드랍되는 돈이 증가합니다.",          90,  0.5f,  nullptr },
    { ItemType::MaxHealth,      L"최대 체력",    L"MaxHealth",      L"최대 체력이 5 증가합니다.",         150, 5,     nullptr },
    { ItemType::Heal20HP,       L"20HP 회복",    L"Heal20HP",       L"체력을 20 회복합니다.",             60,  20,    nullptr },
    { ItemType::MultiShot,      L"멀티샷",       L"MultiShot",      L"발사체가 2개 → 3개로 증가합니다.",  130, 1,     nullptr },
    { ItemType::SplashDamage,   L"스플래쉬",     L"SplashDamage",   L"범위 공격 효과가 추가됩니다.",       140, 1,     nullptr },
    { ItemType::Pierce,         L"관통",         L"Pierce",         L"관통 가능한 횟수가 증가합니다.",     110, 1,     nullptr },
};

std::unordered_map<ItemType, int> PriceIncreaseMap = {
    { ItemType::PlayerSpeed, 50 },
    { ItemType::AttackSpeed, 50 },
    { ItemType::WallPunch, 50 },
    { ItemType::MoneyDrop, 50 },
    { ItemType::MaxHealth, 50 },
    { ItemType::Heal20HP, 50 },
    { ItemType::MultiShot, 50 },
    { ItemType::SplashDamage, 50 },
    { ItemType::Pierce, 50 },
};
std::unordered_set<ItemType> PurchasedItems;
std::unordered_map<ItemType, int> ItemPriceMap;
