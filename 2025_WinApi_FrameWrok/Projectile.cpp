#include "pch.h"
#include "Projectile.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"

Projectile::Projectile() : _angle(0.f), _dir(1.f, 1.f)
{
	_projecTex = GET_SINGLE(ResourceManager)->GetTexture(L"Player_32");
	auto* col = AddComponent<Collider>();
	col->SetName(L"PlayerBullet");
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
}

void Projectile::Update()
{
	Translate({ _dir.x * 500.f * fDT, _dir.y * 500.f * fDT });
}

void Projectile::Render(HDC hdc)
{
	LONG width = _projecTex->GetWidth();
	LONG height = _projecTex->GetHeight();

	//ELLIPSE_RENDER(hdc, _pos.x, _pos.y, _size.x, _size.y);
	ComponentRender(hdc);
}
