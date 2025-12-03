#include "pch.h"
#include "EnemyAttackState.h"
#include "SceneManager.h"
#include "EnemyBullet.h"

void EnemyAttackState::Enter()
{
    _attackCooldown = 0.f;
    _attackRange = 200.f;
}

void EnemyAttackState::Update()
{
    Vec2 enemyPos = _enemy->GetPos();
    Vec2 targetPos = _enemy->_target->GetPos();

    float dx = targetPos.x - enemyPos.x;
    float dy = targetPos.y - enemyPos.y;
    float dist = sqrtf(dx * dx + dy * dy);

    if (dist > _attackRange)
    {
        _enemy->ChangeState("MOVE");
        return;
    }

    _attackCooldown += fDT;

    while (_attackCooldown >= 1.f)
    {
        Attack();
        _attackCooldown -= 1.f;
    }
}


void EnemyAttackState::Render(HDC hdc)
{

}

void EnemyAttackState::Attack()
{
    Vec2 playerPos = _enemy->_target->GetPos();
	Vec2 _pos = _enemy->GetPos();
    EnemyBullet* bullet = new EnemyBullet(_pos, playerPos);
    GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
}
