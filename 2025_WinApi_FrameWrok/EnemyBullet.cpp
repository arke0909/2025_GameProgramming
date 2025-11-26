#include "pch.h"
#include "EnemyBullet.h"
#include "Collider.h"

EnemyBullet::EnemyBullet()
{
	AddComponent<Collider>();
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Update()
{
	Translate({1.f * fDT,1.f}); // 위치 갱신
}

void EnemyBullet::Render(HDC hdc)
{
	Vec2 pos = GetPos();
	Vec2 size = GetSize();
	RECT_RENDER(hdc, pos.x, pos.y
		, size.x, size.y);
	ComponentRender(hdc);
}
