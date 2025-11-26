#pragma once
#include "Collider.h"
class CircleCollider :
    public Collider
{
public:
    CircleCollider();
    ~CircleCollider();
public:
    void Render(HDC hDC);
    void GizmoRender(HDC hDC);
public:
    void SetRadius(float radius) { _radius = radius; }
    const float& GetRadius() const { return _radius; };
private:
    float _radius;
};

