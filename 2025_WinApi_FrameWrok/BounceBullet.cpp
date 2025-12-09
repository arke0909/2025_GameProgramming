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
	_rigidbody = AddComponent<Rigidbody>();
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

	if (set.isVertical)
	{
		_dir.x = -_dir.x;
		Translate({ _dir.x > 0 ? 1.f : -1.f, 0.f });
	}
	else
	{
		_dir.y = -_dir.y;
		Translate({ 0.f, _dir.y > 0 ? 1.f : -1.f });
	}

	_bounceCount++;
	if (_bounceCount >= _maxBounces)
	{
		GET_SINGLE(SceneManager)->RequestDestroy(this);
	}
}
