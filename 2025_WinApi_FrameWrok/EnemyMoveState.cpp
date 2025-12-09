#include "pch.h"
#include "EnemyMoveState.h"

EnemyMoveState::EnemyMoveState(Enemy* owner, std::wstring animetionName)
	: EnemyState(owner, L"MOVE"),
	_speed(100.f),
	_attackRange(200.f),
	_target(nullptr)
{

}

void EnemyMoveState::Update()
{
    if (_enemy->_player == nullptr || _enemy == nullptr)
        return;

    if (IsInAttackRange())
    {
		_enemy->ChangeState("ATTACK");
        return;
    }

    MoveToTarget();
}

void EnemyMoveState::MoveToTarget()
{
    if (_enemy->_player == nullptr) // Enemy 실제 target 사용
        return;

    Vec2 currentPos = _enemy->GetPos();
    Vec2 targetPos = _enemy->_player->GetPos();

    float dx = targetPos.x - currentPos.x;
    float dy = targetPos.y - currentPos.y;

    float len = sqrtf(dx * dx + dy * dy);
    if (len == 0) return;

    float nx = dx / len;
    float ny = dy / len;

    _enemy->MoveBy(Vec2(nx * _speed * fDT, ny * _speed * fDT));
}

bool EnemyMoveState::IsInAttackRange()
{
    if (_enemy->_player == nullptr)
        return false;

    Vec2 target = _enemy->_player->GetPos();
	Vec2 _pos = _enemy->GetPos();
    float dx = target.x - _pos.x;
    float dy = target.y - _pos.y;

    float dist = sqrtf(dx * dx + dy * dy);

    return dist <= GetAttackRange();
}

float EnemyMoveState::GetAttackRange()
{
    return _attackRange;
}