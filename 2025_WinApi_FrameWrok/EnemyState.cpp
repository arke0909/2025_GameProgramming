#include "pch.h"
#include "EnemyState.h"
#include "Enemy.h"

EnemyState::EnemyState(Entity* owner, std::wstring animetionName)
    : EntityState(owner, animetionName)
{
    _enemy = dynamic_cast<Enemy*>(owner);
}
