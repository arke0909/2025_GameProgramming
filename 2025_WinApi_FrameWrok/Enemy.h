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
    void SetTarget(Player* player) { _player = player; };
	Player* GetTarget() const { return _player; }

    void UpdateHP(int value) {
        _hp += value;
        if (_hp < 0)
            _hp = 0;
        if (_hp > _maxHP)
            _hp = _maxHP;
    };
    int GetHP() { return _hp; };
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

    int _hp;
    int _maxHP;
};
