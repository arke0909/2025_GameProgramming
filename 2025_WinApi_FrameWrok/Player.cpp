#include "pch.h"
#include "Player.h"
#include "Weapon.h"
#include "Window.h"
#include "Projectile.h"
#include "Rigidbody.h"
#include "CircleCollider.h"
#include "Animator.h"
#include "StatComponent.h"
#include "Stat.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "GameEvent.h"


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
	_statCompo->AddStat(STAT_SPEED, 250);
	_statCompo->AddStat(STAT_WEAPONSPEED, 800);
	_statCompo->AddStat(STAT_WALLFORCE, 60);
	_statCompo->AddStat(STAT_GOLDMULTI, 1);

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
	float moveSpeed = _statCompo->GetValue(STAT_SPEED);
	_rigidbody->SetVelocity(velocity * moveSpeed);

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
		//ShotProjectile();
		_weapon->PullWeapon();
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
	weapon->SetWindow(_inGameWindow);

	GET_SINGLE(SceneManager)->GetCurScene()
		->AddObject(weapon, Layer::BULLET);

	return weapon;
}

void Player::ShotProjectile()
{
	//float time = GET_SINGLE(TimeManager)->GetTime();
	//float currentLapse = time - _lastFireTime;

	////if (currentLapse < _statCompo->GetValue(STAT_ATTACKSPEED))

	//_lastFireTime = time;

	//Vec2 mousePos = GET_SINGLE(InputManager)->GetMousePos();
	//Vec2 dir = mousePos - _pos;

	////int splashLvl = _statCompo->GetValue(STAT_SPLASH);
	////int damageLvl = _statCompo->GetValue(STAT_ATTACK);
	////int bulletCnt = (int)_statCompo->GetValue(STAT_WEAPON_SIZE);

	//float baseAngle = atan2(dir.y, dir.x);

	//float term = _bulletTermAngle * PI / 180.f;

	//float start = -(bulletCnt - 1) * term * 0.5f;

	//for (int i = 0; i < bulletCnt; ++i)
	//{
	//	//Projectile* proj = new Projectile(splashLvl);

	//	float angle = baseAngle + start + term * i;
	//	float x = cos(angle);
	//	float y = sin(angle);

	//	//proj->Init(_pos, { x, y });
	//	//proj->SetWallForce(_statCompo->GetValue(STAT_WALLFORCE));
	//	//proj->SetPenetration(_statCompo->GetValue(STAT_PENET));

	//	//GET_SINGLE(SceneManager)->GetCurScene()
	//	//	->AddObject(proj, Layer::BULLET);
	//}
}

void Player::AfterInit()
{
	_weapon = CreateWeapon();
	_weapon->SetWallForce(_statCompo->GetValue(STAT_WALLFORCE));
	_weapon->AddSpeed(_statCompo->GetValue(STAT_WEAPONSPEED));

	GameEvents::OnItemPurchased
		.Subscribe([this](const ItemInfo& item)
			{
				std::wcout << item.name;
				auto* targetStat = _statCompo->GetStat(item.name);
				if (targetStat != nullptr)
				{
					int currentModifyCount = targetStat->GetModifyCnt();
					wstring str = std::format(L"{0}{1}", item.name, currentModifyCount);
					targetStat->AddModifier(str, item.value);
				}
				else if (item.name == HEAL)
				{
					GET_SINGLE(GameManager)->playerHealth += item.value;
				}
				else if (item.name == STAT_WEAPONSPEED)
				{
					_weapon->AddSpeed(item.value);
				}
				else if (item.name == STAT_WEAPON_SIZE)
				{
					_weapon->SizeUp(item.value);
				}
				else if (item.name == STAT_SPLASH)
				{
					_weapon->SetSplashLevelUp(item.value);
				}
			});

	//_lastFireTime = -_statCompo->GetValue(STAT_ATTACKSPEED);
}
