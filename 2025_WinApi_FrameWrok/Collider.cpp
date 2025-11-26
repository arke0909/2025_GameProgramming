#include "pch.h"
#include "Collider.h"
#include "Object.h"
UINT Collider::m_nextID = 0;
Collider::Collider() : m_updatedPos{ 0.f,0.f }, m_offsetPos{ 0.f, 0.f }, m_ID(m_nextID++),
_showDebug()
{

}

Collider::~Collider()
{
}

void Collider::Init()
{
}

void Collider::LateUpdate()
{
	Object* owner = GetOwner();
	Vec2 pos = owner->GetPos();
	m_updatedPos = pos + m_offsetPos;
}

void Collider::Render(HDC hDC)
{
	PenType colorPen = PenType::GREEN;
	if (_showDebug)
		colorPen = PenType::RED;
	GDISelector pen(hDC, colorPen);
	GDISelector brush(hDC, BrushType::HOLLOW);

	(this->*fp)(hDC);
}


void Collider::EnterCollision(Collider* _other)
{
	_showDebug = true;
	GetOwner()->EnterCollision(_other);
}

void Collider::StayCollision(Collider* _other)
{
	GetOwner()->StayCollision(_other);
}

void Collider::ExitCollision(Collider* _other)
{
	_showDebug = false;
	GetOwner()->ExitCollision(_other);
}
