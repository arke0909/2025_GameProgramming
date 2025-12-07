#pragma once
#include "EntityState.h"
#include "PhaseData.h"
#include "EnemyBoss.h"

class EnemyBossAttackState :
    public EntityState
{
public:
    EnemyBossAttackState(EnemyBoss* owner, std::wstring animetionName);

    void Enter() override;
    void Update() override;
    void Exit() override;

    void Render(HDC hdc) override {};

private:
    void SelectNextPattern(); // 실행할 패턴 선택
    void ExecuteCurrentPattern(); // 패턴 실행

    EnemyBoss* _owner;
    float _attackTimer;
    int _currentPatternIndex;
};