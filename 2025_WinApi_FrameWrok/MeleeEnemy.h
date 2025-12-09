#pragma once
#include "Enemy.h"
class MeleeEnemy :
    public Enemy
{
public:
    MeleeEnemy();
    ~MeleeEnemy() override;
	void EnterCollision(Collider* _other) override;
private:
    float _attackRange;

    void Update() override { Enemy::Update(); };
    void Render(HDC hdc) override { Enemy::Render(hdc); };
};
