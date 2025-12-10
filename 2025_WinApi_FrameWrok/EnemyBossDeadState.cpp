#include "pch.h"
#include "EnemyBossDeadState.h"
#include "EnemySpawnManager.h"
#include "SceneManager.h"

EnemyBossDeadState::EnemyBossDeadState(EnemyBoss* owner, std::wstring animationName)
    : EntityState(owner, L"DEAD"),
    _owner(owner),
    _deathTime(2.0f),
    _currentTime(0.0f)
{
}

EnemyBossDeadState::~EnemyBossDeadState()
{
}

void EnemyBossDeadState::Enter()
{
    EntityState::Enter();
    _currentTime = 0.0f;
}

void EnemyBossDeadState::Update()
{
    EntityState::Update();
    _currentTime += fDT;

    if (_currentTime >= _deathTime)
    {
        GET_SINGLE(EnemySpawnManager)->DeadEnemy(_owner);
    }
}

void EnemyBossDeadState::Exit()
{
    EntityState::Exit();
}