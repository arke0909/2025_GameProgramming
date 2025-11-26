#include "pch.h"
#include "Weapon.h"
#include "Player.h"
#include "Rigidbody.h"
#include "ResourceManager.h"
#include "CircleCollider.h"
#include "Animator.h"

Weapon::Weapon()
{
	_wTex = GET_SINGLE(ResourceManager)
		->GetTexture(L"Player_32");
	_rigidbody = AddComponent<Rigidbody>();
	_rigidbody->SetUseGravity(false);
	auto* col = AddComponent<CircleCollider>();
	col->SetName(L"Weapon");

	Vec2 animSize;

	switch (_wTex->GetHeight())
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
		_wTex,
		{ 0.f,0.f },
		animSize,//{1024.f,1024.f},
		{ 0.f,0.f },
		1, 1
	);

	animator->Play(L"Idle");
}

Weapon::~Weapon()
{
}

void Weapon::Update()
{
}

void Weapon::Render(HDC hdc)
{
	ComponentRender(hdc);
}

void Weapon::PullWeapon()
{
	Vec2 pPos = _player->GetPos();
	Vec2 dir = pPos - _pos;
	dir.Normalize();

	_rigidbody->SetVelocity({});
	_rigidbody->AddImpulse(dir * _moveSpeed);
}