#pragma once
#include "EnemyState.h"
class EnemyOnlyAttackState
	: public EnemyState
{
public:

	EnemyOnlyAttackState(Enemy* owner, std::wstring animetionName)
		: EnemyState(owner, L"OnlyAttack") {}
	void Enter() override;
	void Update() override;
	void Render(HDC hdc) override {};

	void Attack();
public:
	float _attackCooldown;
};

