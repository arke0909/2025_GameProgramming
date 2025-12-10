#pragma once
#include "Enemy.h"
class CircleShotEnemy :
    public Enemy
{
public:
    CircleShotEnemy();
	~CircleShotEnemy() override = default;

private:
    void Update() override;
    void Attack();

private:
    float _coolTime;
	float _accTime;
};

