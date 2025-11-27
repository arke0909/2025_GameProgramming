#pragma once
#include "Enemy.h"
class RangedEnemy :
    public Enemy
{
public:
    RangedEnemy();
    ~RangedEnemy() override;

protected:
	void Update() override;
	void Attack() override;
    float GetAttackRange() override;

private:
    float _attackRange;
	float _attackCooldown;
	bool _canAttack;
};