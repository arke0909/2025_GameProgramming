#include "pch.h"
#include "RangedEnemy.h"
#include "ResourceManager.h"
#include "EnemyBullet.h"
#include "SceneManager.h"
#include "EnemyAttackState.h"
#include "EnemyMoveState.h"
#include "EnemySpawnManager.h"
#include "Animator.h"

RangedEnemy::RangedEnemy()
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
    animator->CreateAnimation(L"MOVE", _eTex, { 0.f, 0.f }, animSize, { 0.f, 0.f }, 1, 1);
    animator->CreateAnimation(L"ATTACK", _eTex, { 0.f, 0.f }, animSize, { 0.f, 0.f }, 1, 1);
    _speed = 100.f;

    _stateMachine = new EntityStateMachine();
    EnemyMoveState* moveState = new EnemyMoveState(this, L"MOVE");
    moveState->_attackRange = 200.f;
    _stateMachine->AddState("MOVE", moveState);
    EnemyAttackState* attackState = new EnemyAttackState(this, L"ATTACK");
    attackState->_attackRange = 200.f;
    _stateMachine->AddState("ATTACK", attackState);
    _stateMachine->ChangeState("MOVE");
}

RangedEnemy::~RangedEnemy()
{
}

void RangedEnemy::EnterCollision(Collider* _other)
{
    if (_other->GetName() == L"Weapon") {
        GET_SINGLE(EnemySpawnManager)->DeadEnemy(this);
    }
}
