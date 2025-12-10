#include "pch.h"
#include "EnemyBossIdleState.h"

EnemyBossIdleState::EnemyBossIdleState(EnemyBoss* owner, std::wstring animationName)
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
	EntityState::Enter();
	_currentTime = 0.0f;
	_maxTime = 2.0f;
}

void EnemyBossIdleState::Update()
{
	EntityState::Update();
	_currentTime += fDT;

	if (_currentTime >= _maxTime)
	{
		_owner->ChangeState("ATTACK");
	}
}

void EnemyBossIdleState::Exit()
{
	EntityState::Exit();
	_currentTime = 0.0f;
}