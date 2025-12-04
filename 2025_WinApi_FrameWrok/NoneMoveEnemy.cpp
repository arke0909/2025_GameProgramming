#include "pch.h"
#include "NoneMoveEnemy.h"
#include "WindowManager.h"
#include "ResourceManager.h"
#include "EnemySpawnManager.h"
#include "EnemyAttackState.h"
#include "EnemyOnlyAttackState.h"

NoneMoveEnemy::NoneMoveEnemy()
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
    animator->CreateAnimation(L"OnlyAttack",
        _eTex,
        { 0.f, 0.f },
        animSize,
        { 0.f, 0.f },
        1, 1);

    _stateMachine = new EntityStateMachine();
    EnemyOnlyAttackState* attackState = new EnemyOnlyAttackState(this, L"OnlyAttack");
    _stateMachine->AddState("OnlyAttack", attackState);
    _stateMachine->ChangeState("OnlyAttack");

   
}

NoneMoveEnemy::~NoneMoveEnemy()
{

}

void NoneMoveEnemy::CreateEnemyWindow()
{
    Vec2 pos = this->GetPos();

    _window = GET_SINGLE(WindowManager)->CreateSubWindow(
        L"NonemoveEnemy",
        {
            { pos.x, pos.y },
            { 250, 250 }
        });
}


void NoneMoveEnemy::EnterCollision(Collider* _other)
{
    if (_other->GetName() == L"Weapon") {
        GET_SINGLE(EnemySpawnManager)->DeadEnemy(this);
    }
}
