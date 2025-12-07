#include "pch.h"
#include "EnemyBossAttackState.h"
#include <random>

EnemyBossAttackState::EnemyBossAttackState(EnemyBoss* owner, std::wstring animetionName)
	: EntityState(owner, L"ATTACK"),
	_owner(owner),
	_attackTimer(0.0f),
	_currentPatternIndex(0)
{
}

void EnemyBossAttackState::Enter()
{
	_attackTimer = 0.0f;
	SelectNextPattern();
}

void EnemyBossAttackState::Update()
{
	PhaseData currentPhase = _owner->GetCurrentPhaseData();

	_attackTimer += fDT;

	if (_attackTimer >= currentPhase.attackInterval)
	{
		ExecuteCurrentPattern();
		_attackTimer = 0.0f;
		SelectNextPattern();
	}
}

void EnemyBossAttackState::Exit()
{
	_attackTimer = 0.0f;
}

void EnemyBossAttackState::SelectNextPattern()
{
	PhaseData currentPhase = _owner->GetCurrentPhaseData();

	if (currentPhase.patterns.empty())
		return;

	_currentPatternIndex = 0;

	int randomValue = rand() % 100 + 1;
	int currentPercent = 0;

	for (int i = 0; i < currentPhase.patterns.size(); ++i)
	{
		currentPercent += (int)currentPhase.patterns[i].weight;
		if (randomValue <= currentPercent)
		{
			_currentPatternIndex = i;
			break;
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
	}
}