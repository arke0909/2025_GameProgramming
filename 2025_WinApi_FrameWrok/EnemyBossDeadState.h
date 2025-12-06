#pragma once
#include "EntityState.h"
#include "EnemyBoss.h"

class EnemyBossDeadState : public EntityState
{
public:
    EnemyBossDeadState(EnemyBoss* owner, std::wstring animationName);
    ~EnemyBossDeadState();

    void Enter() override;
    void Update() override;
    void Exit() override;
    void Render(HDC hdc) override {};

private:
    EnemyBoss* _owner;
    float _deathTime;
    float _currentTime;
};