#pragma once
#include "EnemyBullet.h"
#include "Rigidbody.h"

class BounceBullet :
    public EnemyBullet
{
public:
    BounceBullet(const Vec2& startPos, const Vec2& targetPos, float speed);
    ~BounceBullet();

    void EnterCollision(Collider* _other);
private:
    Rigidbody* _rigidbody;
    int _bounceCount;
    int _maxBounces;
};
