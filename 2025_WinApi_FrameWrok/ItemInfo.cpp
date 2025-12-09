#include "pch.h"
#include "ItemInfo.h"

std::vector<ItemInfo> AllItems = {
    { ItemType::BulletSpeed,  L"탄속", L"탄환 속도를 증가시킨다.", 100, nullptr },
    { ItemType::AttackSpeed,  L"공속", L"공격 속도를 증가시킨다.", 120, nullptr },
    { ItemType::WallPunch,    L"월펀치", L"벽 밀림 강도 증가", 80, nullptr },
    { ItemType::MoneyDrop,    L"재력", L"드랍 돈 증가", 90, nullptr },
    { ItemType::MaxHealth,    L"최대 체력", L"최대 체력 +5", 150, nullptr },
    { ItemType::Heal20HP,     L"20HP 회복", L"그냥 회복", 60, nullptr },
    { ItemType::MultiShot,    L"멀티샷", L"2발 → 3발", 130, nullptr },
    { ItemType::SplashDamage, L"스플래쉬", L"범위 공격 증가", 140, nullptr },
    { ItemType::Pierce,       L"관통", L"관통 횟수 증가", 110, nullptr },
};
