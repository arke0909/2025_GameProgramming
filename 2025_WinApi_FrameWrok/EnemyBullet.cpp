#include "pch.h"
#include "EnemyBullet.h"
#include "BoxCollider.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameManager.h"

EnemyBullet::EnemyBullet(const Vec2& startPos, const Vec2& targetPos, float speed)
{
	_speed = speed;

	auto* col = AddComponent<BoxCollider>();
	col->SetName(L"EnemyBullet");
	col->SetTrigger(true);

	_eTex = GET_SINGLE(ResourceManager)
		->GetTexture(L"EnumyBullet");

	Vec2 animSize;

	switch (_eTex->GetHeight())
	{
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
		L"Bullet",
		_eTex,
		{ 0.f,0.f },
		animSize,
		{ 0.f,0.f },
		1, 1
	);

	animator->Play(L"Bullet");
    SetPos(startPos);

    Vec2 dir;
    dir.x = targetPos.x - startPos.x;
    dir.y = targetPos.y - startPos.y;

    float length = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0)
        _dir = dir / length;

	_screenSize.x = SCREEN_WIDTH;
	_screenSize.y = SCREEN_HEIGHT;
	_halfSize = animSize * 0.5f;
}

EnemyBullet::~EnemyBullet()
{	
	
}

void EnemyBullet::Update()
{
    Translate(_dir * _speed * fDT);
	Vec2 pos = GetPos();

	if (pos.x + _halfSize.x <= 0 ||
		pos.y + _halfSize.y <= 0 ||
		pos.x - _halfSize.x >= _screenSize.x ||
		pos.y - _halfSize.y >= _screenSize.y)
	{
		GET_SINGLE(SceneManager)->RequestDestroy(this);

	}
}

void EnemyBullet::Render(HDC hdc)
{
    ComponentRender(hdc);
}

void EnemyBullet::EnterCollision(Collider* _other)
{
	if (_other->GetName() == L"Player") {
		GET_SINGLE(GameManager)->playerHealth--;
		GET_SINGLE(SceneManager)->RequestDestroy(this);
		this->SetDead();
	}
}
