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
		->GetTexture(L"Zoombie");

	auto* health = AddComponent<EntityHealthComponent>();
	health->SetHealth(2);

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

void ArmorEnemy::EnterCollision(Collider* _other)
{
    if (_other->GetName() == L"Weapon" || _other->GetName() == L"Splash")
    {
        auto* health = GetComponent<EntityHealthComponent>();
		health->UpdateHP(-1);
		int currentHP = health->GetCurrentHP();
		GET_SINGLE(ResourceManager)->Play(L"EnemyHitSound");
        if (currentHP <= 0) {
            GET_SINGLE(ResourceManager)->Play(L"EnemyDieSound");
            GET_SINGLE(EnemySpawnManager)->DeadEnemy(this);
        }
    }
}
