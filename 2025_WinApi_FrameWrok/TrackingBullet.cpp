#include "pch.h"
#include "TrackingBullet.h"

TrackingBullet::TrackingBullet(Vec2 startPos, Player* target, float speed, float trackingStrength)
    : EnemyBullet(startPos, target->GetPos(), speed),
    _target(target),
    _trackingStrength(trackingStrength)
{
    _direction = _dir;
}

TrackingBullet::~TrackingBullet()
{
}

void TrackingBullet::Update()
{
    if (_target == nullptr)
    {
        Translate(_dir * _speed * fDT);
        return;
    }

    Vec2 currentPos = GetPos();
    Vec2 targetPos = _target->GetPos();

    float dx = targetPos.x - currentPos.x;
    float dy = targetPos.y - currentPos.y;
    float len = sqrtf(dx * dx + dy * dy);

    if (len > 0)
    {
        float targetDirX = dx / len;
        float targetDirY = dy / len;

        _direction.x = _direction.x * (1.0f - _trackingStrength) + targetDirX * _trackingStrength;
        _direction.y = _direction.y * (1.0f - _trackingStrength) + targetDirY * _trackingStrength;

        float dirLen = sqrtf(_direction.x * _direction.x + _direction.y * _direction.y);
        if (dirLen > 0)
        {
            _direction.x /= dirLen;
            _direction.y /= dirLen;
        }

        _dir = _direction;
    }

    EnemyBullet::Update();
}