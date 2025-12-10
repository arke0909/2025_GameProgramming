#include "pch.h"
#include "EnemyMeleeAttackState.h"
#include "GameManager.h"

EnemyMeleeAttackState::EnemyMeleeAttackState(Enemy* owner, std::wstring animationName)
	: EnemyState(owner, L"ATTACK"),
	_coolTime(2.5f),
	_currentTime(0.0f)
{
}

EnemyMeleeAttackState::~EnemyMeleeAttackState()
{
}

void EnemyMeleeAttackState::Enter()
{
	EnemyState::Enter();
	_isAttack = true;
	cout << "Melee Attack State Entered" << endl;
}

void EnemyMeleeAttackState::Update()
{
	EnemyState::Update();
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
