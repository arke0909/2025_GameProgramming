#pragma once
#include "EnemyState.h"
class EnemyMoveState :
    public EnemyState
{
public:
    EnemyMoveState(Enemy* owner, std::wstring animetionName);
    void Update() override;
public:
    void MoveToTarget();
	bool IsInAttackRange();
    float GetAttackRange();
public:
	Object* _target;
    float _speed;
	float _attackRange;

    void Render(HDC hdc) override {};
};
