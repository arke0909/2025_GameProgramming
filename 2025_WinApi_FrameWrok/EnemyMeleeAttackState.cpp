#include "pch.h"
#include "EnemyMeleeAttackState.h"
#include "GameManager.h"

EnemyMeleeAttackState::EnemyMeleeAttackState(Enemy* owner, std::wstring animationName)
	: EnemyState(owner, L"ATTACK"),
	_coolTime(1.5f),
	_currentTime(1.5f)
{
	_attackRange = owner->GetAttackRange();
}

EnemyMeleeAttackState::~EnemyMeleeAttackState()
{
}

void EnemyMeleeAttackState::Enter()
{
	EnemyState::Enter();
	_isAttack = true;
}

void EnemyMeleeAttackState::Update()
{
	EnemyState::Update();

	Vec2 enemyPos = _enemy->GetPos();
	Vec2 targetPos = _enemy->GetTarget()->GetPos();

	float dx = targetPos.x - enemyPos.x;
	float dy = targetPos.y - enemyPos.y;
	float dist = sqrtf(dx * dx + dy * dy);

	if (dist > _attackRange)
	{
		_enemy->ChangeState("MOVE");
		return;
	}

	if (_isAttack) {
		_currentTime += fDT;
	}

	if (_coolTime <= _currentTime) {
		Attack();
		_currentTime = 0.0f;
	}
}

void EnemyMeleeAttackState::Exit()
{
	EnemyState::Exit();
	_isAttack = false;
}

void EnemyMeleeAttackState::Attack()
{
	GET_SINGLE(GameManager)->playerHealth--;
}
