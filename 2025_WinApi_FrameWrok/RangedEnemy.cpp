#include "pch.h"
#include "RangedEnemy.h"
#include "ResourceManager.h"

RangedEnemy::RangedEnemy()
{
    m_pTex = GET_SINGLE(ResourceManager)->GetTexture(L"RangedEnemy");
    _attackRange = 200.0f;
}

RangedEnemy::~RangedEnemy()
{
}

void RangedEnemy::Attack()
{

}

float RangedEnemy::GetAttackRange()
{
    return _attackRange;
}