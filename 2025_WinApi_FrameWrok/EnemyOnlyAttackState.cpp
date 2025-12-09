#include "pch.h"
#include "SceneManager.h"
#include "EnemyOnlyAttackState.h"
#include "EnemyBullet.h"

void EnemyOnlyAttackState::Enter()
{
    EntityState::Enter();
	_attackCooldown = 0.f;
}

void EnemyOnlyAttackState::Update()
{
    Vec2 enemyPos = _enemy->GetPos();
    Vec2 targetPos = _enemy->GetTarget()->GetPos();

    float dx = targetPos.x - enemyPos.x;
    float dy = targetPos.y - enemyPos.y;
    float dist = sqrtf(dx * dx + dy * dy);

    _attackCooldown += fDT;

    while (_attackCooldown >= 3.5f)
    {
        Attack();
        _attackCooldown -= 3.5f;
    }
}

void EnemyOnlyAttackState::Attack()
{
    Vec2 playerPos = _enemy->GetTarget()->GetPos();
    Vec2 _pos = _enemy->GetPos();
    EnemyBullet* bullet = new EnemyBullet(_pos, playerPos,200.0f);
    GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
}
