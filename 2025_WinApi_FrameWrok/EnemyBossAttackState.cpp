#include "pch.h"
#include "EnemyBossAttackState.h"
#include <random>

EnemyBossAttackState::EnemyBossAttackState(EnemyBoss* owner, std::wstring animationName)
	: EntityState(owner, L"ATTACK"),
	_owner(owner),
	_attackTimer(0.0f),
	_currentPatternIndex(0)
{
}

void EnemyBossAttackState::Enter()
{
	EntityState::Enter();

	const PhaseData& phase = _owner->GetCurrentPhaseData();

	_patternCooldowns.clear();
	_patternCooldowns.resize(phase.patterns.size(), 0.f);

	_attackTimer = 0.f;
	SelectNextPattern();
}

void EnemyBossAttackState::Update()
{
	EntityState::Update();

	float dt = fDT;

	for (float& time : _patternCooldowns)
	{
		if (time > 0.f)
			time -= dt;
	}

	_attackTimer += dt;

	const PhaseData& currentPhase = _owner->GetCurrentPhaseData();

	if (_attackTimer >= currentPhase.attackInterval)
	{
		ExecuteCurrentPattern();

		if (_currentPatternIndex < _patternCooldowns.size())
		{
			_patternCooldowns[_currentPatternIndex] =
				currentPhase.patterns[_currentPatternIndex].collTime;
		}

		_attackTimer = 0.f;
		SelectNextPattern();
	}
}

void EnemyBossAttackState::Exit()
{
	EntityState::Exit();
	_attackTimer = 0.0f;
}

void EnemyBossAttackState::SelectNextPattern()
{
	const PhaseData& phase = _owner->GetCurrentPhaseData();

	int totalWeight = 0;
	for (size_t i = 0; i < phase.patterns.size(); ++i)
	{
		if (_patternCooldowns[i] <= 0.f)
			totalWeight += (int)phase.patterns[i].weight;
	}

	if (totalWeight == 0)
	{
		_currentPatternIndex = 0;
		return;
	}

	int randomValue = rand() % totalWeight;
	int acc = 0;

	for (size_t i = 0; i < phase.patterns.size(); ++i)
	{
		if (_patternCooldowns[i] > 0.f)
			continue;

		acc += (int)phase.patterns[i].weight;
		if (randomValue < acc)
		{
			_currentPatternIndex = (int)i;
			return;
		}
	}
}

void EnemyBossAttackState::ExecuteCurrentPattern()
{
	PhaseData currentPhase = _owner->GetCurrentPhaseData();

	if (_currentPatternIndex >= currentPhase.patterns.size())
		return;

	const PatternData& pattern = currentPhase.patterns[_currentPatternIndex];

	switch (pattern.patternType)
	{
	case PatternType::CIRCLESHOT:
		_owner->ExecuteCircleShot(pattern);
		break;
	case PatternType::LINEARSHOT:
		_owner->ExecuteLinearShot(pattern);
		break;
	case PatternType::BOUNCESHOT:
		_owner->ExecuteBounceShot(pattern);
		break;
	case PatternType::TRACKINGSHOT:
		_owner->ExecuteTrackingShot(pattern);
		break;
	case PatternType::MOVESPRAYSHOT:
		_owner->ExecuteMoveSprayShot(pattern);
		break;
	case PatternType::WARPBLAST:
		_owner->ExecuteCircularSector(pattern);
		break;
	}
}