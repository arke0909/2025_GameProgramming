#pragma once
#include "Enemy.h"
class RangedEnemy :
    public Enemy
{
public:
    RangedEnemy();
    ~RangedEnemy() override = default;

private:
	void EnterCollision(Collider* _other) override {
		Enemy::EnterCollision(_other);
	};
	void Update() override {
		Enemy::Update();
	};
};