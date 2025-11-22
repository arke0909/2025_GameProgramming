#include "pch.h"
#include "Player.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "Animator.h"
#include "InputManager.h"
#include "ResourceManager.h"

Player::Player()
{
	_pTex = GET_SINGLE(ResourceManager)
		->GetTexture(L"Player");
	_rigidBody = AddComponent<Rigidbody>();
	_rigidBody->SetUseGravity(false);
	AddComponent<Collider>();

	auto* animator = AddComponent<Animator>();
	animator->CreateAnimation
	(
		L"Idle",
		_pTex,
		{0.f,0.f},
		{1024.f,1024.f},
		{0.f,0.f},
		1,1
	);

	animator->Play(L"Idle");
}

Player::~Player()
{
	SAFE_DELETE(_rigidBody);
}

void Player::Update()
{
	Vec2 velocity{0,0};

	if (GET_KEY(KEY_TYPE::W))
		velocity.y -= 1;
	if (GET_KEY(KEY_TYPE::S))
		velocity.y += 1;
	if (GET_KEY(KEY_TYPE::A))
		velocity.x -= 1;
	if (GET_KEY(KEY_TYPE::D))
		velocity.x += 1;

	velocity.Normalize();
	_rigidBody->SetVelocity(velocity * _moveSpeed);
}

void Player::Render(HDC hdc)
{
	ComponentRender(hdc);
}
