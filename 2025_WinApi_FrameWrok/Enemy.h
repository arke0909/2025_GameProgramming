#pragma once
#include "Object.h"
class Enemy :
    public Object
{
public:
	Enemy();
	~Enemy();
	void Death();
	void SetDirection();
	void MoveToTarget();
public:
	virtual void Attack();
public:
    Vec2 _targetPos;
private:
	float _speed;
	float _attackDamage;
	float _direction;
};
