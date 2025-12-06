#pragma once
#include "EntityState.h"
#include "EnemyBoss.h"

class EnemyBossHitState : public EntityState
{
public:
    EnemyBossHitState(EnemyBoss* owner, std::wstring animationName);
    ~EnemyBossHitState();

    void Enter() override;
    void Update() override;
    void Exit() override;
    void Render(HDC hdc) override {};

private:
    EnemyBoss* _owner;
    float _hitStunTime;
    float _currentTime;
};