#include "pch.h"
#include "EffectParticle.h"
#include "EasingManager.h"

EffectParticle::EffectParticle()
{
}

EffectParticle::~EffectParticle()
{
}

void EffectParticle::Update()
{
	Translate(_dir * fDT * _speed);

	_ease = GET_SINGLE(EasingManager)->InQuint(_timer / _lifeTime);
	_currentRadius = std::lerp(_targetRadius, 0, _ease);
	_timer += GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_timer >= _lifeTime)
		SetDead();
}

void EffectParticle::Render(HDC hdc)
{
	Graphics graphics(hdc);
	float alpha = std::lerp(255, 0, _ease);
	SolidBrush brush(Color(alpha, 255, 255, 255));
	RectF rect(
		(int)(_pos.x - _currentRadius / 2),
		(int)(_pos.y - _currentRadius / 2),
		(int)(_currentRadius),
		(int)(_currentRadius)
	);
	graphics.FillEllipse(&brush, rect);
}
