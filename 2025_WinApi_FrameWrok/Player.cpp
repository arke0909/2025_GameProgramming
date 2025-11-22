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
		->GetTexture(L"Player_96");
	_rigidBody = AddComponent<Rigidbody>();
	_rigidBody->SetUseGravity(false);
	AddComponent<Collider>();

	Vec2 animSize;

	switch (_pTex->GetHeight())
	{
	case 16:
		animSize = { 16.f,16.f };
		break;
	case 32:
		animSize = { 32.f,32.f };
		break;
	case 48:
		animSize = { 48.f,48.f };
		break;
	case 64:
		animSize = { 64.f,64.f };
		break;
	case 96:
		animSize = { 96.f,96.f };
		break;
	case 128:
		animSize = { 128.f,128.f };
		break;
	}

	auto* animator = AddComponent<Animator>();
	animator->CreateAnimation
	(
		L"Idle",
		_pTex,
		{0.f,0.f},
		animSize,//{1024.f,1024.f},
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
