#include "pch.h"
#include "EnemyIdleState.h"

EnemyIdleState::EnemyIdleState(Enemy* owner, std::wstring animetionName)
	: EnemyState(owner, L"IDLE")
{
	
}

void EnemyIdleState::Update()
{
}
