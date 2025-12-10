#include "pch.h"
#include "Splash.h"
#include "CircleCollider.h"
#include "EasingManager.h"


Splash::Splash(int level)
{ 
	_damage *= level;
	_cirCol = AddComponent<CircleCollider>();
	_cirCol->SetName(L"Splash");
}

Splash::~Splash()
{

}

void Splash::Update()
{
	_ease = GET_SINGLE(EasingManager)->OutCirc(_timer / _duration);
	_currentRadius = std::lerp(0, _targetRadius, _ease);
	_cirCol->SetRadius(_currentRadius);
	_timer += GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_timer >= _duration)
		SetDead();
}

void Splash::Render(HDC hdc)
{
	Graphics graphics(hdc);
	float alpha = std::lerp(255, 0, _ease);
	Pen pen(Color(alpha, 255, 255, 255));
	RectF rect(
		(int)(_pos.x - _currentRadius / 2),
		(int)(_pos.y - _currentRadius / 2),
		(int)(_currentRadius),
		(int)(_currentRadius)
	);
	graphics.DrawEllipse(&pen, rect);
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
