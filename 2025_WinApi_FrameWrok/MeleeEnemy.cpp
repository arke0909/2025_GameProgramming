#include "pch.h"
#include "MeleeEnemy.h"
#include "ResourceManager.h"
#include "Animator.h"

MeleeEnemy::MeleeEnemy()
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
