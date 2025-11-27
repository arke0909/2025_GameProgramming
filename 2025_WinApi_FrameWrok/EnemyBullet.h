#pragma once
#include "Object.h"
#include "Animator.h"

class EnemyBullet 
    : public Object
{
public:
    EnemyBullet(const Vec2& startPos, const Vec2& targetPos);
    ~EnemyBullet();

    void Update() override;
    void Render(HDC hdc) override;
	void EnterCollision(Collider* _other) override;

private:
    Texture* _pTex;
    Vec2 _dir;
    float _speed;
};
