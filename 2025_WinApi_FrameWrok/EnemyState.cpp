#include "pch.h"
#include "EnemyState.h"
#include "Enemy.h"

EnemyState::EnemyState(Enemy* owner, std::wstring animetionName)
    : EntityState(owner, animetionName)
{
    _enemy = owner;
}
