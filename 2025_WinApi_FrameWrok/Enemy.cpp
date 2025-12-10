#include "pch.h"
#include "Enemy.h"
#include <cmath> 
#include "BoxCollider.h"
#include "SceneManager.h"
#include "EnemySpawnManager.h"
#include "ResourceManager.h"
#include "EnemyMoveState.h"
#include "Player.h"

Enemy::Enemy()
    : _player(nullptr),
    _speed(100.f),
    _stateMachine(nullptr)
{
    auto* col = AddComponent<BoxCollider>();
    col->SetName(L"Enemy");
    col->SetTrigger(true);
}

Enemy::~Enemy()
{
    delete _stateMachine;
}

void Enemy::Update()
{
	Entity::Update();
	_stateMachine->UpdateStateMachine();
}

void Enemy::Render(HDC hdc)
{
	Entity::Render(hdc);
	ComponentRender(hdc);
}

void Enemy::EnterCollision(Collider* _other)
{
    if (_other->GetName() == L"Player")
    {
		_other->GetOwner()->SetDead();
        GET_SINGLE(SceneManager)->RequestDestroy(_other->GetOwner());
    }

    if (_other->GetName() == L"PlayerBullet") 
    {
        UpdateHP(-10);
        if (GetHP() <= 0) {
            GET_SINGLE(EnemySpawnManager)->DeadEnemy(this);
        }
    }
}

void Enemy::ChangeState(std::string state)
{
	_stateMachine->ChangeState(state);
}
