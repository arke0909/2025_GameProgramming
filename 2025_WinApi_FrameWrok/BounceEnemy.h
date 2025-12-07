#pragma once
#include "Enemy.h"
class BounceEnemy :
    public Enemy
{
public:
    BounceEnemy();
    ~BounceEnemy() override;
	void EnterCollision(Collider* _other) override;
};
