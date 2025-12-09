#include "pch.h"
#include "Splash.h"
#include "CircleCollider.h"

Splash::Splash(int level)
{
	_damage *= level;
	_cirCol = AddComponent<CircleCollider>();
}

Splash::~Splash()
{

}

void Splash::Update()
{
	_currentRadius = std::lerp(0, _targetRadius, _timer / _duration);
	_cirCol->SetRadius(_currentRadius);
	_timer += GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_timer >= _duration)
		SetDead();
}

void Splash::Render(HDC hdc)
{
	ELLIPSE_RENDER(hdc, _pos.x, _pos.y, _currentRadius, _currentRadius);
}

void Splash::EnterCollision(Collider* _other)
{
	// 대미지 로직 처리
}

void Splash::StayCollision(Collider* _other)
{
}

void Splash::ExitCollision(Collider* _other)
{
}
