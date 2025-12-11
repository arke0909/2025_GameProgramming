#include "pch.h"
#include "Weapon.h"
#include "Player.h"
#include "Rigidbody.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "CircleCollider.h"
#include "Animator.h"
#include "Wall.h"
#include "Splash.h"
#include "Effect.h"

Weapon::Weapon()
{
	_rigidbody = AddComponent<Rigidbody>();
	_rigidbody->SetUseGravity(false);
	_rigidbody->SetAirDrag(1.f);
	auto* col = AddComponent<CircleCollider>();
	col->SetName(L"Weapon");
	col->SetRadius(_currentRadius);
	col->SetTrigger(false);
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
	ELLIPSE_RENDER(hdc, _pos.x, _pos.y, _currentRadius * 2, _currentRadius * 2);
}

void Weapon::EnterCollision(Collider* _other)
{
	auto* effect = new Effect();
	effect->SetPos(_pos);
	effect->CreateParticle(13, 10, 80, 50, 0.5f, 0.2f, 30, 10);
	effect->SetColor(Color(255, 255, 255, 255));
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(effect, Layer::EFFECT);


	if(_other->GetName() == L"Enemy")
		if (_splashLvl > 0)
			CreateSplash();

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

void Weapon::SizeUp(float value)
{
	_currentRadius += value;
	auto* col = GetComponent<CircleCollider>();
	col->SetRadius(_currentRadius);
}

void Weapon::CreateSplash()
{
	Splash* splash = new Splash(_splashLvl);
	splash->SetPos(_pos);
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(splash, Layer::BULLET);
}