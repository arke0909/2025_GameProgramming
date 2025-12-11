#include "pch.h"
#include "WindowManager.h"
#include "EnemyBoss.h"
#include "BoxCollider.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "EnemyBossIdleState.h"
#include "EnemyBossAttackState.h"
#include "BounceBullet.h"
#include "TrackingBullet.h"
#include "PhaseData.h"
#include "EnemyBossDeadState.h"
#include "EnemyBullet.h"

EnemyBoss::EnemyBoss()
	: _currentPhase(0)
{
	_eTex = GET_SINGLE(ResourceManager)
		->GetTexture(L"Pumpkin");

	auto* health = AddComponent<EntityHealthComponent>();
	health->SetHealth(100);

	Vec2 animSize = { 32.f, 32.f };
	if (_eTex)
	{
		switch (_eTex->GetHeight())
		{
		case 64: animSize = { 64.f, 64.f }; break;
		case 96: animSize = { 96.f, 96.f }; break;
		default: animSize = { 32.f, 32.f }; break;
		}
	}

	auto* animator = AddComponent<Animator>();
	animator->CreateAnimation(L"IDLE", _eTex, { 0.f, 0.f }, animSize, { 0.f, 0.f }, 1, 1);
	animator->CreateAnimation(L"ATTACK", _eTex, { 0.f, 0.f }, animSize, { 0.f, 0.f }, 1, 1);
	animator->CreateAnimation(L"DEAD", _eTex, { 0.f, 0.f }, animSize, { 0.f, 0.f }, 1, 1);

	InitializePhases();
		
	_stateMachine = new EntityStateMachine();
	_stateMachine->AddState("IDLE", new EnemyBossIdleState(this, L"IDLE"));
	_stateMachine->AddState("ATTACK", new EnemyBossAttackState(this, L"ATTACK"));
	_stateMachine->AddState("DEAD", new EnemyBossDeadState(this, L"DEAD"));
	_stateMachine->ChangeState("IDLE");
}

EnemyBoss::~EnemyBoss()
{
	GET_SINGLE(WindowManager)->CloseSubWindow(_window);
}

void EnemyBoss::InitializePhases()
{
	PhaseData phase1;
	phase1.attackInterval = 1.0f;
	phase1.patterns =
	{
		{ PatternType::CIRCLESHOT, 1.4f, 50.0f, 150.0f },
		{ PatternType::LINEARSHOT, 1.0f, 30.0f, 150.0f },
		{ PatternType::WARPBLAST, 3.0f, 20.f, 220.f },
	};

	PhaseData phase2;
	phase2.attackInterval = 0.9f;
	phase2.patterns =
	{
		{ PatternType::CIRCLESHOT, 1.2f, 40.0f, 150.0f },
		{ PatternType::BOUNCESHOT, 4.0f, 30.0f, 150.0f },
		{ PatternType::MOVESPRAYSHOT, 5.0f, 10.f, 220.f },
		{ PatternType::WARPBLAST, 3.0f, 20.f, 220.f }
	};

	PhaseData phase3;
	phase3.attackInterval = 0.8f;
	phase3.patterns =
	{
		{ PatternType::CIRCLESHOT, 1.0f, 30.0f, 170.0f },
		{ PatternType::TRACKINGSHOT, 2.0f, 20.0f, 170.0f },
		{ PatternType::MOVESPRAYSHOT, 3.0f, 20.f, 220.f },
		{ PatternType::BOUNCESHOT, 5.0f, 20.0f, 160.0f },
		{ PatternType::WARPBLAST, 3.0f, 10.f, 220.f }
	};

	_phases.push_back(phase1);
	_phases.push_back(phase2);
	_phases.push_back(phase3);
}

void EnemyBoss::CreateEnemyWindow()
{
	Vec2 pos = GetPos();

	_window = (BossWindow*)GET_SINGLE(WindowManager)->CreateSubWindow<BossWindow>(
		L"Boss",
		{
			{ pos.x, pos.y },
			{ 600, 600 }
		});
}

void EnemyBoss::Update()
{
	Entity::Update();
	CheckPhaseTransition();

	if (_isMoving)
	{
		Vec2 pos = GetPos();
		Vec2 dir = _moveTarget - pos;
		float dist = dir.Length();

		if (dist < 1.f)
		{
			SetPos(_moveTarget);
			_isMoving = false;
			_window->WindowMoveAndChangeSize(_window->GetWindowSize(), _moveTarget);
		}
		else
		{
			dir.Normalize();
			Vec2 newPos = pos + dir * _moveSpeed * fDT;
			SetPos(newPos);

			_window->WindowMoveAndChangeSize(_window->GetWindowSize(), newPos);
		}
	}


	if (_isSprayMoving)
	{
		_sprayTime += fDT;
		_sprayAccTime += fDT;

		if (_sprayAccTime >= _sprayInterval)
		{
			_sprayAccTime = 0.f;

			Vec2 bossPos = GetPos();
			Vec2 playerPos = _player->GetPos();

			Vec2 dir = playerPos - bossPos;
			dir.Normalize();

			float spread = (rand() % 20 - 10) * (PI / 180.f);
			float baseAngle = atan2f(dir.y, dir.x);
			float rad = baseAngle + spread;

			Vec2 target = bossPos + Vec2(cosf(rad), sinf(rad)) * 900.f;

			EnemyBullet* bullet = new EnemyBullet(bossPos, target, 220.f);
			GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
			GET_SINGLE(ResourceManager)->Play(L"BossShotSound");
		}

		if (_sprayTime >= _sprayDuration)
		{
			_isSprayMoving = false;
		}
	}

	_stateMachine->UpdateStateMachine();
}

void EnemyBoss::Render(HDC hdc)
{
	Enemy::Render(hdc);
}

void EnemyBoss::ChangeState(std::string state)
{
	_stateMachine->ChangeState(state);
}

void EnemyBoss::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"PlayerBullet")
	{

		int damage = 10;
		if (_currentPhase == 0)
			damage = 8;
		else if (_currentPhase == 1)
			damage = 6;
		else if (_currentPhase == 2) 
			damage = 4;

		auto* healthComp = GetComponent<EntityHealthComponent>();
		healthComp->UpdateHP(-10);
		GET_SINGLE(ResourceManager)->Play(L"EnemyDieSound");
		if (healthComp->GetCurrentHP() <= 0)
		{
			ChangeState("DEAD");
		}
	}
}

PhaseData EnemyBoss::GetCurrentPhaseData() const
{
	if (_currentPhase >= 0 && _currentPhase < (int)_phases.size())
		return _phases[_currentPhase];

	return PhaseData();
}

void EnemyBoss::CheckPhaseTransition()
{
	auto* healthComp = GetComponent<EntityHealthComponent>();

	float hpRatio = ((float)healthComp->GetCurrentHP() / (float)healthComp->GetMaxHP()) * 100.0f;

	if (hpRatio > 66.0f)
	{
		if (_currentPhase != 0)
			TransitionToPhase(0);
	}
	else if (hpRatio > 33.0f)
	{
		if (_currentPhase != 1)
			TransitionToPhase(1);
	}
	else
	{
		if (_currentPhase != 2)
			TransitionToPhase(2);
	}
}

void EnemyBoss::TransitionToPhase(int phase)
{
	if (phase < 0 || phase >= (int)_phases.size())
		return;

	_currentPhase = phase;
}

void EnemyBoss::ExecuteDistanceMoveSkill()
{
	Vec2 bossPos = GetPos();
	Vec2 playerPos = _player->GetPos();
	Vec2 diff = bossPos - playerPos;
	float distance = diff.Length();

	Vec2 moveDir = { 0.f, 0.f };

	if (fabs(diff.x) > fabs(diff.y))
		moveDir.x = (diff.x >= 0.f) ? 1.f : -1.f;
	else
		moveDir.y = (diff.y >= 0.f) ? 1.f : -1.f;

	if (distance < _minDistance)
	{
	}
	else if (distance > _maxDistance)
	{
		moveDir = moveDir * -1.f;
	}
	else
	{
		return;
	}

	Vec2 target = bossPos + moveDir * _moveStep;
	target.x = max(0.f, min(target.x, (float)SCREEN_WIDTH));
	target.y = max(0.f, min(target.y, (float)SCREEN_HEIGHT));

	_moveTarget = target;
	_isMoving = true;
}

void EnemyBoss::ExecuteCircleShot(const PatternData& pattern)
{
	ExecuteDistanceMoveSkill();
	Vec2 bossPos = this->GetPos();

	int bulletCount = 8;
	for (int i = 0; i < bulletCount; ++i)
	{
		float angle = (float)(rand() % 360 + 1);
		float radian = angle * (PI / 180.0f);

		Vec2 targetPos;
		targetPos.x = bossPos.x + cosf(radian) * 1000.0f;
		targetPos.y = bossPos.y + sinf(radian) * 1000.0f;

		EnemyBullet* bullet = new EnemyBullet(bossPos, targetPos, pattern.speed);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
		GET_SINGLE(ResourceManager)->Play(L"BossShotSound");
	}
}

void EnemyBoss::ExecuteLinearShot(const PatternData& pattern)
{
	ExecuteDistanceMoveSkill();
	Vec2 playerPos = _player->GetPos();
	Vec2 pos = GetPos();
	EnemyBullet* bullet = new EnemyBullet(pos, playerPos, pattern.speed);
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
	GET_SINGLE(ResourceManager)->Play(L"BossShotSound");
}

void EnemyBoss::ExecuteBounceShot(const PatternData& pattern)
{
	ExecuteDistanceMoveSkill();
	Vec2 playerPos = _player->GetPos();
	Vec2 pos = GetPos();
	BounceBullet* bullet = new BounceBullet(pos, playerPos, pattern.speed);
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
	GET_SINGLE(ResourceManager)->Play(L"BossShotSound");
}

void EnemyBoss::ExecuteTrackingShot(const PatternData& pattern)
{
	ExecuteDistanceMoveSkill();
	Vec2 pos = GetPos();
	TrackingBullet* bullet = new TrackingBullet(pos, _player, pattern.speed);
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
	GET_SINGLE(ResourceManager)->Play(L"BossShotSound");
}

void EnemyBoss::ExecuteMoveSprayShot(const PatternData& pattern)
{
	Vec2 bossPos = GetPos();
	Vec2 playerPos = _player->GetPos();

	Vec2 toPlayer = playerPos - bossPos;
	toPlayer.Normalize();

	Vec2 moveDir = { -toPlayer.y, toPlayer.x };

	if (rand() % 2 == 0)
		moveDir = moveDir * -1.f;

	Vec2 target = bossPos + moveDir * 250.f;
	target.x = max(0.f, min(target.x, (float)SCREEN_WIDTH));
	target.y = max(0.f, min(target.y, (float)SCREEN_HEIGHT));

	_moveTarget = target;
	_moveSpeed = 300.f;

	_isMoving = true;
	_isSprayMoving = true;

	_sprayTime = 0.f;
	_sprayAccTime = 0.f;
	_sprayInterval = 0.07f;
	_sprayDuration = 0.9f;
}

void EnemyBoss::ExecuteCircularSector(const PatternData& pattern)
{
	Vec2 bossPos = GetPos();
	Vec2 playerPos = _player->GetPos();

	Vec2 dir = playerPos - bossPos;
	dir.Normalize();

	float baseAngle = atan2f(dir.y, dir.x);
	float spread = 30.f * (PI / 180.f);
	int bulletCount = 4;

	for (int i = 0; i < bulletCount; ++i)
	{
		float t = 0.f;
		if (bulletCount > 1)
			t = (float)i / (bulletCount - 1);

		float angle = baseAngle - spread * 0.5f + spread * t;
		Vec2 target = bossPos + Vec2(cosf(angle), sinf(angle)) * 1000.f;

		EnemyBullet* bullet = new EnemyBullet(bossPos, target, pattern.speed);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
		GET_SINGLE(ResourceManager)->Play(L"BossShotSound");
	}
}