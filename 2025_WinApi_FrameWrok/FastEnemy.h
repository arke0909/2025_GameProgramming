#pragma once
#include "Enemy.h"
class FastEnemy :
    public Enemy
{
public:
    FastEnemy();
	~FastEnemy() = default;
private:
	void EnterCollision(Collider* _other) override {
		Enemy::EnterCollision(_other);
	};
	void Update() override {
		Enemy::Update();
	};
};

