#include "pch.h"
#include "BounceEnemy.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Rigidbody.h"
#include "EnemyMoveState.h"

BounceEnemy::BounceEnemy()
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
    _speed = 150.f;

    _stateMachine = new EntityStateMachine();
    EnemyMoveState* moveState = new EnemyMoveState(this, L"MOVE");
    moveState->_attackRange = 0;
    _stateMachine->AddState("MOVE", moveState);
    _stateMachine->ChangeState("MOVE");
}

BounceEnemy::~BounceEnemy()
{
	
}

void BounceEnemy::EnterCollision(Collider* _other)
{
    if (_other->GetName() == L"Weapon")
    {
        if (_target == nullptr)
            return;

        Rigidbody* rigidbody = _other->GetOwner()->GetComponent<Rigidbody>();
        if (rigidbody == nullptr)
            return;

        Vec2 playerPos = _target->GetPos();
        Vec2 weaponPos = _other->GetOwner()->GetPos();

        Vec2 direction = playerPos - weaponPos;
        direction.Normalize();

        Vec2 newVelocity = direction * 500.0f;

        rigidbody->SetVelocity(newVelocity);

		this->SetDead();
		GET_SINGLE(SceneManager)->RequestDestroy(this);
    }
}
