#include "pch.h"
#include "ItemInfo.h"

std::vector<ItemInfo> AllItems = {
    { ItemType::PlayerSpeed,  L"이속",STAT_SPEED, L"플레이어의 속도를 증가시킨다.", 100, nullptr },
    { ItemType::AttackSpeed,  L"공속",STAT_ATTACKSPEED, L"공격 속도를 증가시킨다.", 120, nullptr },
    { ItemType::WallPunch,    L"월펀치",STAT_WALLFORCE, L"벽 밀림 강도 증가", 80, nullptr },
    { ItemType::MoneyDrop,    L"재력",STAT_GOLDMULTI, L"드랍 돈 증가", 90, nullptr },
    { ItemType::MaxHealth,    L"최대 체력",STAT_HP, L"최대 체력 +5", 150, nullptr },
    { ItemType::Heal20HP,     L"20HP 회복",L"Recovery", L"그냥 회복", 60, nullptr},
    { ItemType::MultiShot,    L"멀티샷",STAT_MULTISHOT, L"2발 → 3발", 130, nullptr },
    { ItemType::SplashDamage, L"스플래쉬",STAT_SPLASH, L"범위 공격 증가", 140, nullptr },
    { ItemType::Pierce,       L"관통",STAT_PENET, L"관통 횟수 증가", 110, nullptr },
};
