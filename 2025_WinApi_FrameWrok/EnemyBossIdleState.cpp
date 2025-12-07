#include "pch.h"
#include "EnemyBossIdleState.h"

EnemyBossIdleState::EnemyBossIdleState(EnemyBoss* owner, std::wstring animetionName)
	: EntityState(owner, L"IDLE"),
	_owner(owner),
	_maxTime(2.0f),
	_currentTime(0.0f)
{
}

EnemyBossIdleState::~EnemyBossIdleState()
{
}

void EnemyBossIdleState::Enter()
{
	_currentTime = 0.0f;
	_maxTime = 2.0f;
}

void EnemyBossIdleState::Update()
{
	_currentTime += fDT;

	if (_currentTime >= _maxTime)
	{
		_owner->ChangeState("ATTACK");
	}
}

void EnemyBossIdleState::Exit()
{
	_currentTime = 0.0f;
}