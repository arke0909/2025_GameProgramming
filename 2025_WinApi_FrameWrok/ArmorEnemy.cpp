#include "pch.h"
#include "ArmorEnemy.h"
#include "ResourceManager.h"
#include "EnemyMoveState.h"
#include "EnemySpawnManager.h"
#include "EnemyMeleeAttackState.h"
#include "SceneManager.h"

ArmorEnemy::ArmorEnemy()
{
	_eTex = GET_SINGLE(ResourceManager)
		->GetTexture(L"CloseEnemy");


    GetComponent<EntityHealthComponent>()->SetHealth(30);

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
    animator->CreateAnimation(L"ATTACK",
        _eTex,
        { 0.f, 0.f },
        animSize,
        { 0.f, 0.f },
        1, 1);

    _speed = 50.f;
    _attackRange = 0.f;
	_dropGold = 70;

    _stateMachine = new EntityStateMachine();
    _stateMachine->AddState("MOVE", new EnemyMoveState(this, L"MOVE"));
    _stateMachine->AddState("ATTACK", new EnemyMeleeAttackState(this, L"ATTACK"));
    _stateMachine->ChangeState("MOVE");
}
