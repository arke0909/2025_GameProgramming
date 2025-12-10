#include "pch.h"
#include "NoneMoveEnemy.h"
#include "WindowManager.h"
#include "ResourceManager.h"
#include "EnemySpawnManager.h"
#include "EnemyMoveState.h"
#include "EnemyAttackState.h"

NoneMoveEnemy::NoneMoveEnemy()
{
    _eTex = GET_SINGLE(ResourceManager)
        ->GetTexture(L"CloseEnemy");

    GetComponent<EntityHealthComponent>()->SetHealth(20);

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
    animator->CreateAnimation(L"ATTACK",
        _eTex,
        { 0.f, 0.f },
        animSize,
        { 0.f, 0.f },
        1, 1);
    animator->CreateAnimation(L"MOVE",
        _eTex,
        { 0.f, 0.f },
        animSize,
        { 0.f, 0.f },
        1, 1);

    _speed = 0.0f;
    _attackRange = SCREEN_WIDTH * 2;
    cout << _attackRange << endl;

    _stateMachine = new EntityStateMachine();
    _stateMachine->AddState("ATTACK", new EnemyAttackState(this, L"ATTACK"));
    _stateMachine->AddState("MOVE", new EnemyMoveState(this, L"MOVE"));
    _stateMachine->ChangeState("ATTACK");
    
}

void NoneMoveEnemy::CreateEnemyWindow()
{
    Vec2 pos = GetPos();

    _window = GET_SINGLE(WindowManager)->CreateSubWindow<Window>(
        L"NonemoveEnemy",
        {
            { pos.x, pos.y },
            { 250, 250 }
        });
}
