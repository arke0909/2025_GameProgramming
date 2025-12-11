#include "pch.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider() : _radius{30}
{
	fp = (void (Collider::*)(HDC))& CircleCollider::GizmoRender;
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Render(HDC hDC)
{
	Collider::Render(hDC);
}

void CircleCollider::GizmoRender(HDC hDC)
{
	//ELLIPSE_RENDER(hDC, m_updatedPos.x, m_updatedPos.y, _radius * 2, _radius * 2);
}