#pragma once
#include "EnemyState.h"
#include <wtypes.h>
class EnemyArmorMoveState :
    public EnemyState
{
public:
	EnemyArmorMoveState(Enemy* owner, std::wstring animetionName);
	void Update() override;
	void MoveToTarget();
	bool IsInAttackRange();
	float GetAttackRange();
	void Exit() override;
public:
	Object* _target;
	float _speed;
	float _attackRange;

	void Render(HDC hdc) override {};
};

