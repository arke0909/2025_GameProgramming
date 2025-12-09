#include "pch.h"
#include "BounceBullet.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Wall.h"
#include "BoxCollider.h"

BounceBullet::BounceBullet(const Vec2& startPos, const Vec2& targetPos, float speed)
	: EnemyBullet(startPos, targetPos, speed),
	_bounceCount(0),
	_maxBounces(3)
{
	_rigidbody = AddComponent<Rigidbody>();
}

BounceBullet::~BounceBullet()
{

}

void BounceBullet::EnterCollision(Collider* _other)
{
	EnemyBullet::EnterCollision(_other);

	if (_other->GetName() == L"Wall")
	{
		auto* wall = dynamic_cast<Wall*>(_other->GetOwner());
		if (!wall) return;
		WallSet set = wall->GetWall();

		Vec2 normal = {};

		if (set.isVertical)
			normal = { 1, 0 };
		else
			normal = { 0, -1 };

		if (!set.isStart)
			normal *= -1;

		Vec2 velocity = _rigidbody->GetVelocity();

		float dot = normal.Dot(-velocity);

		Vec2 reflection = velocity + ((normal * 2) * dot);

		_rigidbody->SetVelocity(reflection);
		_bounceCount++;
		if (_bounceCount >= _maxBounces) {
			GET_SINGLE(SceneManager)->RequestDestroy(this);
		}
	}
}
