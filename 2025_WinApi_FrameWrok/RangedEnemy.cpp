#include "pch.h"
#include "RangedEnemy.h"
#include "ResourceManager.h"
#include "EnemyBullet.h"
#include "SceneManager.h"

RangedEnemy::RangedEnemy()
    :_attackCooldown(1.f),
    _canAttack(true)
{
    m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"RangedEnemy");
    _attackRange = 200.0f;
}

RangedEnemy::~RangedEnemy()
{
}

void RangedEnemy::Update()
{
    if (!_canAttack)
    {
        _attackCooldown += fDT;
        if (_attackCooldown >= 1.f)
        {
            _canAttack = true;
            _attackCooldown = 0.f;
        }
    }

	Enemy::Update();
}

void RangedEnemy::Attack()
{
    if (_canAttack)
    {
		cout << "Ranged Enemy Attack!" << endl;
        _canAttack = false;
        GET_SINGLE(SceneManager)->GetCurScene()->
            Spawn<EnemyBullet>(Layer::PROJECTILE, _pos, {10, 10});
    }
}

float RangedEnemy::GetAttackRange()
{
    return _attackRange;
}