#include "pch.h"
#include "Projectile.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "CircleCollider.h"
#include "Animator.h"
#include "Rigidbody.h"
#include "Splash.h"
#include "Effect.h"

Projectile::Projectile(int level, int splashLvl) : _angle(0.f), _dir(1.f, 1.f)
{
	_damage *= level; 
	_splashLvl = splashLvl;
	_projecTex = GET_SINGLE(ResourceManager)->GetTexture(L"Bullet");
	_rigidbody = AddComponent<Rigidbody>();
	_rigidbody->SetUseGravity(false);
	auto* col = AddComponent<CircleCollider>();
	col->SetName(L"PlayerBullet");
	col->SetRadius(10.f);
	col->SetTrigger(true);

	Vec2 animSize;

	switch (_projecTex->GetHeight())
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
		_projecTex,
		{ 0.f,0.f },
		animSize,//{1024.f,1024.f},
		{ 0.f,0.f },
		1, 1
	);

	animator->Play(L"Idle");
}

Projectile::~Projectile()
{
	Object::~Object();
}

void Projectile::Update()
{
}

void Projectile::Render(HDC hdc)
{
	ComponentRender(hdc);
}

void Projectile::EnterCollision(Collider* _other)
{
	auto* effect = new Effect();
	effect->SetPos(_pos);
	effect->CreateParticle();
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(effect, Layer::BULLET);
	if (_other->GetName() == L"Enemy")
	{
		_penetration--;

		if (_splashLvl > 0)
			CreateSplash();

		if(_penetration == 0)
			SetDead();
	}
	if(_other->GetName() == L"Wall")
		SetDead();
}

void Projectile::StayCollision(Collider* _other)
{
}

void Projectile::ExitCollision(Collider* _other)
{
}

void Projectile::Init(Vec2 pos, Vec2 dir)
{
	SetPos(pos);
	SetDir(dir);
	_rigidbody->SetVelocity(_dir * _moveSpeed);
}

void Projectile::CreateSplash()
{
	Splash* splash = new Splash(_splashLvl);
	splash->SetPos(_pos);
	GET_SINGLE(SceneManager)->GetCurScene()->AddObject(splash, Layer::BULLET);
}
