#include "pch.h"
#include "EnemyAttackState.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "EnemyBullet.h"

EnemyAttackState::EnemyAttackState(Enemy* owner, std::wstring animetionName)
    : EnemyState(owner, L"ATTACK"),
	_attackCooldown(0.f),
	_attackRange(0.f),
    _canAttack(false)
{
    _attackRange = owner->GetAttackRange();
}

void EnemyAttackState::Enter()
{
	EntityState::Enter();
    _attackCooldown = 0.f;
}

void EnemyAttackState::Update()
{
    EntityState::Update();
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

    _attackCooldown += fDT;

    while (_attackCooldown >= 1.f)
    {
        Attack();
        _attackCooldown -= 1.f;
    }
}

void EnemyAttackState::Attack()
{
	Player* player = _enemy->GetTarget();
    if (player == nullptr)
        return;

    Vec2 playerPos = player->GetPos();
	Vec2 _pos = _enemy->GetPos();
    EnemyBullet* bullet = new EnemyBullet(_pos, playerPos, 200.0f);
    GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
    GET_SINGLE(ResourceManager)->Play(L"EnemyShotSound");
}
