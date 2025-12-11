#include "pch.h"
#include "BounceBullet.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Wall.h"
#include "BoxCollider.h"

BounceBullet::BounceBullet(const Vec2& startPos, const Vec2& targetPos, float speed)
	: EnemyBullet(startPos, targetPos, speed),
	_bounceCount(0),
	_maxBounces(7)
{

	auto* col = GetComponent<BoxCollider>();
	col->SetName(L"EnemyBullet");
	col->SetTrigger(false);
}

BounceBullet::~BounceBullet()
{

}

void BounceBullet::EnterCollision(Collider* _other)
{
	if (_other->GetName() != L"Wall")
	{
		EnemyBullet::EnterCollision(_other);
		return;
	}

	auto* wall = dynamic_cast<Wall*>(_other->GetOwner());
	if (!wall) return;

	WallSet set = wall->GetWall();

	Vec2 normal;

	if (set.isVertical)
	{
		normal = set.isStart ? Vec2{ 1.f, 0.f } : Vec2{ -1.f, 0.f };
	}
	else
	{
		normal = set.isStart ? Vec2{ 0.f, 1.f } : Vec2{ 0.f, -1.f };
	}

	if (_dir.Dot(normal) >= 0.f)
		return;

	_dir = _dir - normal * (2.f * _dir.Dot(normal));

	Translate(normal);

	_bounceCount++;
	if (_bounceCount >= _maxBounces)
	{
		GET_SINGLE(SceneManager)->RequestDestroy(this);
	}
}

