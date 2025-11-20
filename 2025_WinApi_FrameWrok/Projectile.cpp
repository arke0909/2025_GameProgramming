#include "pch.h"
#include "Projectile.h"
#include "ResourceManager.h"
#include "Collider.h"

Projectile::Projectile() : _angle(0.f), _dir(1.f,1.f)
{
	_projecTex = GET_SINGLE(ResourceManager)->GetTexture(L"Bullet");
	auto* col = AddComponent<Collider>();
	col->SetName(L"PlayerBullet");
	col->SetTrigger(true);
}

Projectile::~Projectile()
{
}

void Projectile::Update()
{
	Translate({ _dir.x* 500.f * fDT, _dir.y * 500.f * fDT});
}

void Projectile::Render(HDC hdc)
{
	LONG width = _projecTex->GetWidth();
	LONG height = _projecTex->GetHeight();

	::TransparentBlt(hdc
		, (int)(_pos.x - _size.x / 2)
		, (int)(_pos.y - _size.y / 2)
		, width
		, height
		, _projecTex->GetTextureDC()
		, 0, 0, width, height, RGB(255, 0, 255));
	//ELLIPSE_RENDER(hdc, _pos.x, _pos.y, _size.x, _size.y);
	ComponentRender(hdc);
}
