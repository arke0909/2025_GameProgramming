#pragma once
#include "EntityState.h"
#include "Enemy.h"
class EnemyState :
    public EntityState
{
public:
    EnemyState(Entity* owner, std::wstring animetionName);
protected:
    Enemy* _enemy;
};
