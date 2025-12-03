#pragma once
#include "Enemy.h"
class MeleeEnemy :
    public Enemy
{
public:
    MeleeEnemy();
    ~MeleeEnemy() override;

private:
    float _attackRange;
};
