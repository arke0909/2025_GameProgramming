#pragma once
#include "Object.h"
#include "Player.h"
#include "Collider.h"
#include "Animator.h"

class Enemy :
    public Object
{
public:
    Enemy();
    virtual ~Enemy();

    void SetTarget(Player* player);
    void Update() override;
    void Render(HDC hdc) override;
    void EnterCollision(Collider* _other) override;
protected:
    virtual void Attack() = 0;
    virtual float GetAttackRange() = 0;

    void MoveToTarget();
    bool IsInAttackRange();
protected:
    Player* _target;
    Texture* m_pTex;
    float _speed;
};
