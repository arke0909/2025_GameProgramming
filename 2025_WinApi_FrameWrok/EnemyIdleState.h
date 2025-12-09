#pragma once
#include "EnemyState.h"
class EnemyIdleState :
    public EnemyState
{
public:
    EnemyIdleState(Enemy* owner, std::wstring animetionName);
	void Update() override;
};
