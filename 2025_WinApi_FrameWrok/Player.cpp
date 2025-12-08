#include "pch.h"
#include "Player.h"
#include "Weapon.h"
#include "Window.h"
#include "Projectile.h"
#include "Rigidbody.h"
#include "CircleCollider.h"
#include "Animator.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"


Player::Player()
{
	_pTex = GET_SINGLE(ResourceManager)
		->GetTexture(L"Player");
	_rigidbody = AddComponent<Rigidbody>();
	_rigidbody->SetUseGravity(false);
	auto* col = AddComponent<CircleCollider>();
	col->SetTrigger(false);
	col->SetRadius(19.f);
	col->SetName(L"Player");
	_circleColRadius = col->GetRadius();

	_statCompo = AddComponent<StatComponent>();
	static_assert(std::is_same_v<decltype(_statCompo), StatComponent*>,
		"_statCompo is NOT StatComponent* !!");

	_statCompo->AddStat(STAT_HP, 5);
	_statCompo->AddStat(STAT_BULLETSPEED, 400);
	_statCompo->AddStat(STAT_ATTACKSPEED, 1.5f);
	_statCompo->AddStat(STAT_WALLFORCE, 20);
	_statCompo->AddStat(STAT_GOLDMULTI, 1);
	_statCompo->AddStat(STAT_MULTISHOT, 1);
	_statCompo->AddStat(STAT_SPLASH, 0);
	_statCompo->AddStat(STAT_PENET, 1);


	Vec2 animSize = { (float)_pTex->GetWidth() , (float)_pTex->GetHeight() };

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
	_rigidbody->SetVelocity(velocity * _moveSpeed);

	float left = _pos.x - _circleColRadius;
	float right = _pos.x + _circleColRadius;
	float top = _pos.y - _circleColRadius;
	float bottom = _pos.y + _circleColRadius;

	Vec2 lt = GET_LT(_inGameWindow->GetSize(), _inGameWindow->GetPos());

	int x = lt.x;
	int y = lt.y;
	int w = _inGameWindow->GetWindowSize().x + x;
	int h = _inGameWindow->GetWindowSize().y + y;

	if (left < x)
		_pos.x = x + _circleColRadius;
	if(right > w)
		_pos.x = w - _circleColRadius;
	if (top < y)
		_pos.y = y + _circleColRadius;
	if (bottom > h)
		_pos.y = h - _circleColRadius;


	if (GET_KEYDOWN(KEY_TYPE::SPACE))
	{
		ShotProjectile();
		//_weapon->PullWeapon();
	}
}

void Player::Render(HDC hdc)
{
	ComponentRender(hdc);
}

void Player::EnterCollision(Collider* _other)
{
}

void Player::StayCollision(Collider* _other)
{
}

void Player::ExitCollision(Collider* _other)
{
}

Weapon* Player::CreateWeapon()
{
	Weapon* weapon = new Weapon;
	weapon->SetPlayer(this);
	
	srand(time(NULL));

	// -100 ~ 100;
	int x = (rand() % 201) - 100;
	int y = (rand() % 201) - 100;

	x = x < 0 ? std::clamp((float)x, -100.f, -50.f)
		: std::clamp((float)x, 50.f, 100.f);
	y = y < 0 ? std::clamp((float)y, -100.f, -50.f)
		: std::clamp((float)y, 50.f, 100.f);

	weapon->SetPos({_pos.x + x, _pos.y + y});
	weapon->SetSize({50.f, 50.f});

	GET_SINGLE(SceneManager)->GetCurScene()
		->AddObject(weapon, Layer::PROJECTILE);

	return weapon;
}

void Player::ShotProjectile()
{
	// 현재 시간
	float time = GET_SINGLE(TimeManager)->GetTime();
	float currentLapse = time - _lastFireTime;

	if (currentLapse < _fireInterval)
		return;

	_lastFireTime = time;
	
	float bulletSpeed = _statCompo->GetValue(STAT_BULLETSPEED);

	int bulletCnt = (int)_statCompo->GetValue(STAT_MULTISHOT);

	float bulletStartAngle = (bulletCnt / 2 - 1) * _bulletTermAngle;


	for (int i = 0; i < bulletCnt; ++i)
	{
		Projectile* proj = new Projectile(bulletSpeed);
		Vec2 mousePos = GET_SINGLE(InputManager)->GetMousePos();
		Vec2 dir = mousePos - _pos;



		proj->Init(_pos, dir);

		GET_SINGLE(SceneManager)->GetCurScene()->AddObject(proj, Layer::BULLET);
	}
}

void Player::AfterInit()
{
	//_weapon = CreateWeapon();

	_lastFireTime = -_fireInterval;
}
