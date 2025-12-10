#pragma once
#include "Enemy.h"
#include "Window.h"
class NoneMoveEnemy :
    public Enemy
{
public:
    NoneMoveEnemy();
    ~NoneMoveEnemy() override = default;
    void CreateEnemyWindow();

private:
	void EnterCollision(Collider* _other) override {
		Enemy::EnterCollision(_other);
	};
	void Update() override {
		Enemy::Update();
	};

private:
    Window* _window;
};
