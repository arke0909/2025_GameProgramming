#include "pch.h"
#include "EnemyBullet.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "ResourceManager.h"

EnemyBullet::EnemyBullet(const Vec2& startPos, const Vec2& targetPos)
{
	_speed = 200.f;
	auto* col = AddComponent<BoxCollider>();
	col->SetName(L"EnemyBullet");
	col->SetTrigger(true);

	_pTex = GET_SINGLE(ResourceManager)
		->GetTexture(L"Player");

	Vec2 animSize;

	switch (_pTex->GetHeight())
	{
		break;
	case 32:
		animSize = { 32.f,32.f };
		break;
	case 64:
		animSize = { 64.f,64.f };
		break;
	case 96:
		animSize = { 96.f,96.f };
		break;
	}

	auto* animator = AddComponent<Animator>();
	animator->CreateAnimation
	(
		L"Idle",
		_pTex,
		{ 0.f,0.f },
		animSize,
		{ 0.f,0.f },
		1, 1
	);

	animator->Play(L"Idle");
    SetPos(startPos);

    Vec2 dir;
    dir.x = targetPos.x - startPos.x;
    dir.y = targetPos.y - startPos.y;

    float length = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0)
        _dir = dir / length;
}

EnemyBullet::~EnemyBullet()
{
	
}

void EnemyBullet::Update()
{
    Translate(_dir * _speed * fDT);
}


void EnemyBullet::Render(HDC hdc)
{
    ComponentRender(hdc);
}

void EnemyBullet::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"Enemy")
		return;

	if (_other->GetName() == L"Player")
		GET_SINGLE(SceneManager)->RequestDestroy(_other->GetOwner());

	GET_SINGLE(SceneManager)->RequestDestroy(this);
}
