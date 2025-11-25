#include "pch.h"
#include "MeleeEnemy.h"
#include "ResourceManager.h"

MeleeEnemy::MeleeEnemy()
{
	m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"MeleeEnemy");
	_attackRange = 0;
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
