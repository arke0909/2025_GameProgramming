#pragma once
#include "EnemyState.h"
class EnemyMoveState :
    public EnemyState
{
public:
    EnemyMoveState(Enemy* owner, std::wstring animetionName);

private:
    void MoveToTarget();
	bool IsInAttackRange();
    float GetAttackRange();

    void Update() override;
    void Render(HDC hdc) override {};

private:
	Object* _target;
    float _speed;
	float _attackRange;

};
