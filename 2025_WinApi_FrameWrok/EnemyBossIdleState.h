#pragma once
#include "EnemyState.h"
#include "EnemyBoss.h"

class EnemyBossIdleState : public EntityState
{
public:
    EnemyBossIdleState(EnemyBoss* owner, std::wstring animationName);
    ~EnemyBossIdleState();

    void Enter() override;
    void Update() override;
    void Exit() override;

    void Render(HDC hdc) override {};
private:
    EnemyBoss* _owner;
    float _maxTime;
    float _currentTime;
};