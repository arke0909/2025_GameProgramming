#pragma once
#include "Enemy.h"
class MeleeEnemy :
    public Enemy
{
public:
    MeleeEnemy();
    ~MeleeEnemy() override = default;

private:
	void EnterCollision(Collider* _other) override {
		Enemy::EnterCollision(_other);
	};
	void Update() override {
		Enemy::Update();
	};

private:
    float _attackRange;
};
