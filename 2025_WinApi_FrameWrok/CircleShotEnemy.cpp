#include "pch.h"
#include "CircleShotEnemy.h"
#include "EnemyBullet.h"
#include "SceneManager.h"
#include "EnemyAttackState.h"
#include "EnemyMoveState.h"
#include "ResourceManager.h"

CircleShotEnemy::CircleShotEnemy()
	: _coolTime(2.5f),
	_accTime(0.f)
{
	_eTex = GET_SINGLE(ResourceManager)
		->GetTexture(L"CircleEnemy");

	Vec2 animSize;
	switch (_eTex->GetHeight())
	{
	case 32:
		animSize = { 32.f, 32.f };
		break;
	case 64:
		animSize = { 64.f, 64.f };
		break;
	case 96:
		animSize = { 96.f, 96.f };
		break;
	default:
		animSize = { 32.f, 32.f };
		break;
	}

	auto* animator = AddComponent<Animator>();
	animator->CreateAnimation(L"MOVE",
		_eTex,
		{ 0.f, 0.f },
		animSize,
		{ 0.f, 0.f },
		1, 1);
	animator->CreateAnimation(L"ATTACK",
		_eTex,
		{ 0.f, 0.f },
		animSize,
		{ 0.f, 0.f },
		1, 1);

	_speed = 0.0f;
	_attackRange = 250.0f;
	_dropGold = 70;

	_stateMachine = new EntityStateMachine();
	_stateMachine->AddState("MOVE", new EnemyMoveState(this, L"MOVE"));
	_stateMachine->AddState("ATTACK", new EnemyAttackState(this, L"ATTACK"));
	_stateMachine->ChangeState("MOVE");
}

CircleShotEnemy::~CircleShotEnemy()
{
}

void CircleShotEnemy::Update()
{
	Enemy::Update();
	_accTime += fDT;
	if (_accTime >= _coolTime) {
		_accTime = 0.f;
		Attack();
	}
}

void CircleShotEnemy::Attack()
{
	Vec2 bossPos = this->GetPos();

	int bulletCount = 8;
	for (int i = 0; i < bulletCount; ++i)
	{
		float angle = (float)(rand() % 360 + 1);
		float radian = angle * (PI / 180.0f);

		Vec2 targetPos;
		targetPos.x = bossPos.x + cosf(radian) * 1000.0f;
		targetPos.y = bossPos.y + sinf(radian) * 1000.0f;

		EnemyBullet* bullet = new EnemyBullet(bossPos, targetPos, 150);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
		GET_SINGLE(ResourceManager)->Play(L"EnemyShotSound");
	}
}


void CircleShotEnemy::CreateEnemyWindow()
{
	Vec2 pos = GetPos();

	_window = GET_SINGLE(WindowManager)->CreateSubWindow<Window>(
		L"NonemoveEnemy",
		{
			{ pos.x, pos.y },
			{ 250, 250 }
		});
}