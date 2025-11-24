#include "pch.h"
#include "Enemy.h"
#include <cmath> 

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::Death()
{
	
}

void Enemy::Attack()
{
	// 공격 로직 구현
}

void Enemy::SetDirection()
{
	float direction = atan2f(_targetPos.y - _pos.y, _targetPos.x - _pos.x);
	_direction = direction;	
}

void Enemy::MoveToTarget()
{
	float deltaX = cosf(_direction) * _speed * fDT;
	float deltaY = sinf(_direction) * _speed * fDT;
	Translate(Vec2(deltaX, deltaY));
}
