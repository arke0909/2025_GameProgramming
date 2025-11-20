#include "pch.h"
#include "Collider.h"
#include "Object.h"
UINT Collider::m_nextID = 0;
Collider::Collider() : m_size{ 30.f,30.f }
, m_updatedPos{ 0.f,0.f }, m_offsetPos{ 0.f, 0.f }, m_ID(m_nextID++),
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
	::TextOut(hDC, 0, 0, L"¾È³ç", 2);
	GDISelector font(hDC, FontType::TITLE);
	::TextOut(hDC,10, 10, L"ÇÏ¼¼¿ä", 3);

	PenType colorPen = PenType::GREEN;
	if (_showDebug)
		colorPen = PenType::RED;
	GDISelector pen(hDC, colorPen);
	GDISelector brush(hDC, BrushType::HOLLOW);

	RECT_RENDER(hDC, m_updatedPos.x, m_updatedPos.y, m_size.x, m_size.y);
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
