#pragma once
#include "Object.h"
#include "Animator.h"
#include "Entity.h"

class EnemyBullet 
    : public Entity
{
public:
    EnemyBullet(const Vec2& startPos, const Vec2& targetPos, float speed);
    ~EnemyBullet();

    void Update() override;
    void Render(HDC hdc) override;
	void EnterCollision(Collider* _other) override;
    
protected:
    Vec2 _dir;
    Vec2 _screenSize;
    Vec2 _halfSize;

    float _speed;
};
