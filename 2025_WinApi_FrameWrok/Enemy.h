#pragma once
#include "Object.h"
#include "Player.h"
#include "Collider.h"
#include "Animator.h"
#include "Entity.h"
#include "EntityStateMachine.h"

class Enemy :
    public Entity
{
public:

    Enemy();
    virtual ~Enemy();

    void MoveBy(Vec2 delta) { Translate(delta); }
    void SetTarget(Player* player);
    void Update() override;
    void Render(HDC hdc) override;
    virtual void EnterCollision(Collider* _other) override;
    void ChangeState(std::string state);

public:
	EntityStateMachine* _stateMachine; 
    Player* _player;
    float _speed;
};
