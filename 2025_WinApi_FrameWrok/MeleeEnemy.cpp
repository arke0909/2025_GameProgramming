#include "pch.h"
#include "MeleeEnemy.h"
#include "ResourceManager.h"
#include "Animator.h"
#include "EnemyMoveState.h"

MeleeEnemy::MeleeEnemy()
{
    _eTex = GET_SINGLE(ResourceManager)->GetTexture(L"CloseEnemy");

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
    _speed = 150.f;

    _stateMachine = new EntityStateMachine();
    EnemyMoveState* moveState = new EnemyMoveState(this, L"MOVE");
    moveState->_attackRange = 0;
    _stateMachine->AddState("MOVE", moveState);
    _stateMachine->ChangeState("MOVE");
}

MeleeEnemy::~MeleeEnemy()
{
}