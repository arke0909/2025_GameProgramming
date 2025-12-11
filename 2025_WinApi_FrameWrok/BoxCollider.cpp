#include "pch.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider() : m_size{ 30.f,30.f }
{
	fp = (void (Collider::*)(HDC))& BoxCollider::GizmoRender;
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Render(HDC hDC)
{
	Collider::Render(hDC);
}

void BoxCollider::GizmoRender(HDC hDC)
{
	//RECT_RENDER(hDC, m_updatedPos.x, m_updatedPos.y, m_size.x, m_size.y);
}
