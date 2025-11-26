#pragma once
#include "Collider.h"

class BoxCollider :
    public Collider
{
public:
    BoxCollider();
    ~BoxCollider();
public:
    void Render(HDC hDC);
    void GizmoRender(HDC hDC);
public:
    void SetSize(Vec2 _size) { m_size = _size; }
    const Vec2& GetSize() const { return m_size; }
private:
    Vec2 m_size; // 콜라이더 크기
};

