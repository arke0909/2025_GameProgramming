#include "pch.h"
#include "EnemyArmorMoveState.h"
#include "SceneManager.h"
EnemyArmorMoveState::EnemyArmorMoveState(Enemy* owner, std::wstring animetionName)
    : EnemyState(owner, L"AROMORMOVE"),
    _speed(100.f),
    _attackRange(200.f),
    _target(nullptr)
{

}

void EnemyArmorMoveState::Update()
{
    if (_enemy->GetTarget() == nullptr || _enemy == nullptr)
        return;

    if (IsInAttackRange())
    {
        _enemy->ChangeState("ATTACK");
        return;
    }

    MoveToTarget();
}

void EnemyArmorMoveState::MoveToTarget()
{
    if (_enemy->GetTarget() == nullptr)
        return;

    Vec2 currentPos = _enemy->GetPos();
    Vec2 targetPos = _enemy->GetTarget()->GetPos();

    float dx = targetPos.x - currentPos.x;
    float dy = targetPos.y - currentPos.y;

    float len = sqrtf(dx * dx + dy * dy);
    if (len == 0) return;

    float nx = dx / len;
    float ny = dy / len;

    _enemy->MoveBy(Vec2(nx * _speed * fDT, ny * _speed * fDT));
}

bool EnemyArmorMoveState::IsInAttackRange()
{
    if (_enemy->GetTarget() == nullptr)
        return false;

    Vec2 target = _enemy->GetTarget()->GetPos();
    Vec2 _pos = _enemy->GetPos();
    float dx = target.x - _pos.x;
    float dy = target.y - _pos.y;

    float dist = sqrtf(dx * dx + dy * dy);

    return dist <= GetAttackRange();
}

float EnemyArmorMoveState::GetAttackRange()
{
    return _attackRange;
}

void EnemyArmorMoveState::Exit()
{
}
