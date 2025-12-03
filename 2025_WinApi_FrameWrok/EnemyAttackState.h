#pragma once
#include "EnemyState.h"
class EnemyAttackState
	: public EnemyState
{
public:

	EnemyAttackState(Enemy* owner, std::wstring animetionName)
		: EnemyState(owner, L"ATTACK") {}
	void Enter() override;
	void Update() override;
	void Render(HDC hdc) override;

	void Attack();
public:
	float _attackRange;
	float _attackCooldown;
	bool _canAttack;
};

