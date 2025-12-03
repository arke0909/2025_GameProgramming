#include "pch.h"
#include "ArmorEnemy.h"
#include "ResourceManager.h"
#include "EnemyMoveState.h"
#include "EnemyArmorMoveState.h"
#include "SceneManager.h"

ArmorEnemy::ArmorEnemy()
{
	_eTex = GET_SINGLE(ResourceManager)
		->GetTexture(L"CloseEnemy");
    Vec2 animSize;
    switch (_eTex->GetHeight())
    {
    case 32:
        animSize = { 32.f, 32.f };
        break;
    case 64:
        animSize = { 64.f, 64.f };
        break;
    case 96:
        animSize = { 96.f, 96.f };
        break;
    default:
        animSize = { 32.f, 32.f };
        break;
    }


    auto* animator = AddComponent<Animator>();
    animator->CreateAnimation(L"MOVE",
        _eTex, 
        { 0.f, 0.f }, 
        animSize,
        { 0.f, 0.f },
        1, 1);
    animator->CreateAnimation(L"AROMORMOVE",
        _eTex,
        { 0.f, 0.f },
        animSize,
        { 0.f, 0.f },
        1, 1);
    _speed = 100.f;

    _stateMachine = new EntityStateMachine();
    EnemyMoveState* moveState = new EnemyMoveState(this, L"MOVE");
    moveState->_attackRange = 0;
    _stateMachine->AddState("MOVE", moveState);
    EnemyArmorMoveState* armormoveState = new EnemyArmorMoveState(this, L"AROMORMOVE");
    armormoveState->_attackRange = 0;
    _stateMachine->AddState("AROMORMOVE", armormoveState);
    _stateMachine->ChangeState("AROMORMOVE");
}

ArmorEnemy::~ArmorEnemy()
{

}

void ArmorEnemy::Update()
{
    if (_isInvincible)
    {
        _invincibleTime += fDT;
        if (_invincibleTime >= _maxInvincibleTime)
        {
            _isInvincible = false;
            _invincibleTime = 0.f;
        }
    }

    Enemy::Update();
}

void ArmorEnemy::EnterCollision(Collider* _other)
{
    if (_other->GetName() != L"Weapon")
        return;

    if (_isInvincible)
        return;

    _hitCount++;

    if (_hitCount >= 2)
    {
        GET_SINGLE(SceneManager)->RequestDestroy(this);
        return;
    }

    _isInvincible = true;
    _invincibleTime = 0.f;

    _stateMachine->ChangeState("MOVE");
}
