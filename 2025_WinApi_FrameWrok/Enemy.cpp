#include "pch.h"
#include "Enemy.h"
#include <cmath> 
#include "Collider.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Player.h"

Enemy::Enemy()
    :
    m_pTex(nullptr), 
    _speed(100.f),
    _direction(0.f),
	_centerPos(400.f, 300.f) //ÀÓ½Ã°ª
{

}

Enemy::~Enemy()
{

}

void Enemy::SetTarget(Player* player)
{
    _target = player;
}

void Enemy::SetDirection()
{
    if (_target == nullptr)
        return;

    Vec2 t = _target->GetPos();
    float dx = t.x - _pos.x;
    float dy = t.y - _pos.y;
    _direction = atan2f(dy, dx);
}

bool Enemy::IsInAttackRange()
{
    if (_target == nullptr)
        return false;

    Vec2 target = _target->GetPos();
    float dx = target.x - _pos.x;
    float dy = target.y - _pos.y;
    float dist = sqrtf(dx * dx + dy * dy);

    return dist <= GetAttackRange();
}

void Enemy::MoveToTarget()
{
    if (_target == nullptr)
        return;

    Vec2 target = _target->GetPos();
    float dx = target.x - _pos.x;
    float dy = target.y - _pos.y;

    float len = sqrtf(dx * dx + dy * dy);
    if (len == 0) return;

    float nx = dx / len;
    float ny = dy / len;

    Translate(Vec2(nx * _speed * fDT, ny * _speed * fDT));
    /*float dx = _centerPos.x - _pos.x;
    float dy = _centerPos.y - _pos.y;

    float len = sqrtf(dx * dx + dy * dy);
    if (len == 0) return;

    float nx = dx / len;
    float ny = dy / len;

    Translate(Vec2(nx * _speed * fDT, ny * _speed * fDT));*/
}

void Enemy::Update()
{
    if (IsInAttackRange())
    {
        Attack();
        return;
    }

    MoveToTarget();
}

void Enemy::Render(HDC hdc)
{
	ComponentRender(hdc);
}

void Enemy::EnterCollision(Collider* _other)
{
    if (_other->IsTrigger())
    {
        if (_other->GetName() == L"Player")
        {
            GET_SINGLE(SceneManager)->RequestDestroy(this);
            GET_SINGLE(SceneManager)->RequestDestroy(_other->GetOwner());
        }
    }
}
