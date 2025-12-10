#pragma once
#include "Object.h"
#include "Player.h"
#include "Collider.h"
#include "Animator.h"
#include "Entity.h"
#include "EntityStateMachine.h"
#include "EntityHealthComponent.h"


class Enemy :
    public Entity
{
public:
    Enemy();
    virtual ~Enemy();

    void MoveBy(Vec2 delta) { Translate(delta); }
    void SetTarget(Player* player) { _player = player; };
	Player* GetTarget() const { return _player; }

	float GetSpeed() const { return _speed; }
	float GetAttackRange() const { return _attackRange; }

    void Update() override;
    void Render(HDC hdc) override;
    virtual void EnterCollision(Collider* _other) override;
    void ChangeState(std::string state);

protected:
	EntityStateMachine* _stateMachine; 
    Player* _player;

    float _speed;
	float _attackRange;
};
