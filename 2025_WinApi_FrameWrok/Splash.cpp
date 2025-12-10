#include "pch.h"
#include "Splash.h"
#include "CircleCollider.h"
#include "EasingManager.h"
#include <gdiplus.h>
using namespace Gdiplus;

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
	_ease = GET_SINGLE(EasingManager)->OutCirc(_timer / _duration);
	_currentRadius = std::lerp(0, _targetRadius, _ease);
	_cirCol->SetRadius(_currentRadius);
	_timer += GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_timer >= _duration)
		SetDead();
}

void Splash::Render(HDC hdc)
{
	//Graphics graphics(hdc);
	//float alpha = std::lerp(0, 255, _ease);
	//Pen pen(Color(alpha, 0, 0, 0));
	//Pen pen(Color(alpha, 255, 0, 0), 3);
	//graphics.DrawLine(&pen, 10, 10, 200, 10);

	//RECT rt = { (int)(_pos.x - _currentRadius / 2),(int)(_pos.y - _currentRadius / 2),(int)(_pos.x + _currentRadius / 2),(int)(_pos.y + _currentRadius / 2) };
	//graphics.DrawEllipse(&pen,rt);
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
