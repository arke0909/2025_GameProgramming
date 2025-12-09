#pragma once
#include "EnemyBullet.h"
#include "Player.h"
#include "Entity.h"

class TrackingBullet :
    public EnemyBullet
{
public:
    TrackingBullet(Vec2 startPos, Player* target, float speed, float trackingStrength = 0.5f);
    ~TrackingBullet();

    void Update() override;

private:
    Player* _target;
    float _trackingStrength;
    Vec2 _direction;
};

