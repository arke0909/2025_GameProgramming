#pragma once
#include "Enemy.h"
class MeleeEnemy :
    public Enemy
{
public:
    MeleeEnemy();
    ~MeleeEnemy() override;

protected:
    void Attack() override;
    float GetAttackRange() override;

private:
    float _attackRange;
};

