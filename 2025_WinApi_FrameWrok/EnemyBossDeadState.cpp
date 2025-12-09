#include "pch.h"
#include "EnemyBossDeadState.h"
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

   //사망시 효과가 들어갈 예정
}

void EnemyBossDeadState::Update()
{
    EntityState::Update();
    _currentTime += fDT;

    if (_currentTime >= _deathTime)
    {
        GET_SINGLE(SceneManager)->RequestDestroy(_owner);
    }
}

void EnemyBossDeadState::Exit()
{
    EntityState::Exit();
}