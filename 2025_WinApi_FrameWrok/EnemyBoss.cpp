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
#include "EnemyBossHitState.h"
#include "EnemyBossDeadState.h"
#include "EnemyBullet.h"

EnemyBoss::EnemyBoss()
	: _hp(100),
	_maxHP(100),
	_currentPhase(0)
{
	_eTex = GET_SINGLE(ResourceManager)
		->GetTexture(L"Player");

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
	animator->CreateAnimation(L"IDLE",
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
	animator->CreateAnimation(L"HIT",
		_eTex,
		{ 0.f, 0.f },
		animSize,
		{ 0.f, 0.f },
		1, 1);
	animator->CreateAnimation(L"DEAD",
		_eTex,
		{ 0.f, 0.f },
		animSize,
		{ 0.f, 0.f },
		1, 1);
	InitializePhases();

	_stateMachine = new EntityStateMachine();
	_stateMachine->AddState("IDLE", new EnemyBossIdleState(this, L"IDLE"));
	_stateMachine->AddState("ATTACK", new EnemyBossAttackState(this, L"ATTACK"));
	_stateMachine->AddState("HIT", new EnemyBossHitState(this, L"HIT"));
	_stateMachine->AddState("DEAD", new EnemyBossDeadState(this, L"DEAD"));
	_stateMachine->ChangeState("IDLE");
}

EnemyBoss::~EnemyBoss()
{
	delete _stateMachine;
}

void EnemyBoss::InitializePhases()
{
	PhaseData phase1;
	phase1.attackInterval = 1.0f;
	phase1.patterns =
	{
		{ PatternType::CIRCLESHOT, 2.0f, 50.0f, 100.0f},
		{ PatternType::LINEARSHOT, 2.0f, 50.0f, 100.0f}
	};

	PhaseData phase2;
	phase2.attackInterval = 1.2f;
	phase2.patterns =
	{
		{ PatternType::CIRCLESHOT, 5.0f, 50.0f, 100.0f},
		{ PatternType::BOUNCESHOT, 2.0f, 50.0f, 100.0f}
	};

	PhaseData phase3;
	phase3.attackInterval = 1.0f;
	phase3.patterns =
	{
		{ PatternType::CIRCLESHOT, 10.0f, 50.0f, 100.0f},
		{ PatternType::BOUNCESHOT, 2.0f, 25.0f, 100.0f},
		{ PatternType::TRACKINGSHOT, 2.0f, 25.0f, 100.0f}
	};

	_phases.push_back(phase1);
	_phases.push_back(phase2);
	_phases.push_back(phase3);
}

void EnemyBoss::CreateEnemyWindow()
{
	Vec2 pos = this->GetPos();

	_window = GET_SINGLE(WindowManager)->CreateSubWindow<Window>(
		L"Boss",
		{
			{ pos.x, pos.y },
			{ 250, 250 }
		});
}

void EnemyBoss::Update()
{
	Entity::Update();
	CheckPhaseTransition();
	_stateMachine->UpdateStateMachine();
}

void EnemyBoss::Render(HDC hdc)
{
	Entity::Render(hdc);
	ComponentRender(hdc);
}

void EnemyBoss::ChangeState(std::string state)
{
	_stateMachine->ChangeState(state);
}

void EnemyBoss::UpdateHP(int value)
{
	_hp += value;
	if (_hp < 0)
		_hp = 0;
	if (_hp > _maxHP)
		_hp = _maxHP;
}

int EnemyBoss::GetHP()
{
	return _hp;
}

void EnemyBoss::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"Weapon")
	{
		UpdateHP(-10);

		if (_hp > 0)
		{
			ChangeState("HIT");
		}
		else
		{
			ChangeState("DEAD");
		}
	}
}

PhaseData EnemyBoss::GetCurrentPhaseData() const
{
	if (_currentPhase >= 0 && _currentPhase < _phases.size())
		return _phases[_currentPhase];

	return PhaseData();
}

void EnemyBoss::CheckPhaseTransition()
{
	float hpRatio = ((float)_hp / (float)_maxHP) * 100.0f;

	if (hpRatio > 50.0f)
	{
		if (_currentPhase != 0)
			TransitionToPhase(0);
	}
	else if (hpRatio <= 50.0f && hpRatio > 25.0f)
	{
		if (_currentPhase != 1) 
			TransitionToPhase(1);
	}
	else if (hpRatio <= 25.0f)
	{
		if (_currentPhase != 2)
			TransitionToPhase(2);
	}
}

void EnemyBoss::TransitionToPhase(int phase)
{
	if (phase < 0 || phase >= _phases.size())
		return;

	_currentPhase = phase;
}

void EnemyBoss::ExecuteCircleShot(const PatternData& pattern)
{
	Vec2 bossPos = this->GetPos();

	int bulletCount = 8;

	for (int i = 0; i < bulletCount; ++i)
	{
		float angle = (360.0f / bulletCount) * i;
		float radian = angle * (PI / 180.0f);

		float dirX = cosf(radian);
		float dirY = sinf(radian);

		Vec2 targetPos;
		targetPos.x = bossPos.x + dirX * 1000.0f;
		targetPos.y = bossPos.y + dirY * 1000.0f;

		EnemyBullet* bullet = new EnemyBullet(bossPos, targetPos, pattern.speed);
		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
	}
}

void EnemyBoss::ExecuteLinearShot(const PatternData& pattern)
{
	Vec2 playerPos = _player->GetPos();
	Vec2 _pos = this->GetPos();
	EnemyBullet* bullet = new EnemyBullet(_pos, playerPos, pattern.speed);
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
}

void EnemyBoss::ExecuteBounceShot(const PatternData& pattern)
{
	Vec2 playerPos = _player->GetPos();
	Vec2 _pos = this->GetPos();
	BounceBullet* bullet = new BounceBullet(_pos, playerPos, pattern.speed);
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
}

void EnemyBoss::ExecuteTrackingShot(const PatternData& pattern)
{
	Vec2 _pos = this->GetPos();
	TrackingBullet* bullet = new TrackingBullet(_pos, _player, pattern.speed);
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(bullet, Layer::PROJECTILE);
}