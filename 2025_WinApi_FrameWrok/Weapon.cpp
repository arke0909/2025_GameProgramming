#include "pch.h"
#include "Weapon.h"
#include "Player.h"
#include "Rigidbody.h"
#include "ResourceManager.h"
#include "CircleCollider.h"
#include "Animator.h"
#include "Wall.h"

Weapon::Weapon()
{
	_wTex = GET_SINGLE(ResourceManager)
		->GetTexture(L"Player_32");
	_rigidbody = AddComponent<Rigidbody>();
	_rigidbody->SetUseGravity(false);
	auto* col = AddComponent<CircleCollider>();
	col->SetName(L"Weapon");
	col->SetTrigger(false);

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

void Weapon::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"Wall")
	{
		auto* wall = dynamic_cast<Wall*>(_other->GetOwner());
		if (!wall) return;
		WallSet set = wall->GetWall();

		Vec2 normal = {};

		if (set.isVertical)
		// 세로다
			normal = { 1, 0 };
		else
		// 가로다
			normal = { 0, -1 };

		if (!set.isStart)
			normal *= -1;

		Vec2 velocity = _rigidbody->GetVelocity();

		float dot = normal.Dot(-velocity);

		Vec2 reflection = velocity + ((normal * 2) * dot);

		reflection *= 0.5f;

		_rigidbody->SetVelocity(reflection);
	}
}

void Weapon::StayCollision(Collider* _other)
{
}

void Weapon::ExitCollision(Collider* _other)
{
}

void Weapon::PullWeapon()
{
	Vec2 pPos = _player->GetPos();
	Vec2 dir = pPos - _pos;
	dir.Normalize();

	_rigidbody->SetVelocity({});
	_rigidbody->AddImpulse(dir * _moveSpeed);
}