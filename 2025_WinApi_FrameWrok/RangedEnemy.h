#pragma once
#include "Enemy.h"
class RangedEnemy :
    public Enemy
{
public:
    RangedEnemy();
    ~RangedEnemy() override;
	void EnterCollision(Collider* _other) override;
};