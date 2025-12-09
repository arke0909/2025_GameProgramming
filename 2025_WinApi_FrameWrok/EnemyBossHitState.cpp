#include "pch.h"
#include "EnemyBossHitState.h"

EnemyBossHitState::EnemyBossHitState(EnemyBoss* owner, std::wstring animationName)
    : EntityState(owner, L"HIT"),
    _owner(owner),
    _hitStunTime(0.3f),  // 0.3ÃÊ °æÁ÷
    _currentTime(0.0f)
{
}

EnemyBossHitState::~EnemyBossHitState()
{
}

void EnemyBossHitState::Enter()
{
    EntityState::Enter();
    _currentTime = 0.0f;

}

void EnemyBossHitState::Update()
{
    EntityState::Update();
    _currentTime += fDT;

    if (_currentTime >= _hitStunTime)
    {
        if (_owner->GetHP() <= 0)
        {
            _owner->ChangeState("DEAD");
        }
        else
        {
            _owner->ChangeState("IDLE");
        }
    }
}

void EnemyBossHitState::Exit()
{
    EntityState::Exit();
    _currentTime = 0.0f;
}