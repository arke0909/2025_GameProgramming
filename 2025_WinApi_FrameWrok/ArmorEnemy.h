#pragma once
#include "Enemy.h"

class ArmorEnemy : public Enemy
{
public:
    ArmorEnemy();
    ~ArmorEnemy() override;
    void EnterCollision(Collider* _other) override;
    void Update() override;

private:
    bool _isInvincible = false;
    float _invincibleTime = 0.f;
    const float _maxInvincibleTime = 1.0f;
    int _hitCount = 0;
};
