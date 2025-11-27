#include "pch.h"
#include "RangedEnemy.h"
#include "ResourceManager.h"
#include "EnemyBullet.h"
#include "SceneManager.h"

RangedEnemy::RangedEnemy()
    :_attackCooldown(1.f),
    _canAttack(true)
{
    m_pTex = GET_SINGLE(ResourceManager)
        ->GetTexture(L"CloseEnemy");

	Vec2 animSize;

	switch (m_pTex->GetHeight())
	{
		break;
	case 32:
		animSize = { 32.f,32.f };
		break;
	case 64:
		animSize = { 64.f,64.f };
		break;
	case 96:
		animSize = { 96.f,96.f };
		break;
	}

	auto* animator = AddComponent<Animator>();
	animator->CreateAnimation
	(
		L"Idle",
		m_pTex,
		{ 0.f,0.f },
		animSize,//{1024.f,1024.f},
		{ 0.f,0.f },
		1, 1
	);

	animator->Play(L"Idle");
    _speed = 100.f;
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
        _canAttack = false;
        // 플레이어 위치를 받아서 총알 생성
        Vec2 playerPos = _target->GetPos();
		EnemyBullet* bullet = new EnemyBullet(_pos, playerPos);
        GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
    }
}

float RangedEnemy::GetAttackRange()
{
    return _attackRange;
}