#include "pch.h"
#include "MeleeEnemy.h"
#include "ResourceManager.h"

MeleeEnemy::MeleeEnemy()
{
	m_pTex = GET_SINGLE(ResourceManager)
		->GetTexture(L"CloseEnemy");
	_attackRange = 0;
	_speed = 150.f;
}

MeleeEnemy::~MeleeEnemy()
{

}

void MeleeEnemy::Attack()
{

}

float MeleeEnemy::GetAttackRange()
{
	return _attackRange;
}
