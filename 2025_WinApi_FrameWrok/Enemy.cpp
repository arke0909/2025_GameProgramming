#include "pch.h"
#include "Enemy.h"
#include <cmath> 
#include "BoxCollider.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Player.h"

Enemy::Enemy()
    : m_pTex(nullptr), 
    _target(nullptr),
    _speed(100.f)
{
    auto* col = AddComponent<BoxCollider>();
    col->SetName(L"Enemy");
    col->SetTrigger(true);
}

Enemy::~Enemy()
{
    
}

void Enemy::SetTarget(Player* player)
{
    _target = player;
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
    if (len == 0)
        return;

    float nx = dx / len;
    float ny = dy / len;

    Translate(Vec2(nx * _speed * fDT, ny * _speed * fDT));
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
    if (_other->GetName() == L"Player")
    {
		_other->GetOwner()->SetDead();
        GET_SINGLE(SceneManager)->RequestDestroy(_other->GetOwner());
        GET_SINGLE(SceneManager)->RequestDestroy(this);
    }
}
