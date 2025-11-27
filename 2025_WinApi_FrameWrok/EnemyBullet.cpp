#include "pch.h"
#include "EnemyBullet.h"
#include "BoxCollider.h"
#include "SceneManager.h"

EnemyBullet::EnemyBullet(const Vec2& startPos, const Vec2& targetPos)
{
    AddComponent<BoxCollider>();
    SetPos(startPos);

    Vec2 dir;
    dir.x = targetPos.x - startPos.x;
    dir.y = targetPos.y - startPos.y;

    float length = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length != 0)
        _dir = dir / length;
}

EnemyBullet::~EnemyBullet()
{
	
}

void EnemyBullet::Update()
{
    Translate(_dir * _speed * fDT);
}


void EnemyBullet::Render(HDC hdc)
{
    Vec2 pos = GetPos();
    Vec2 size = GetSize();
    RECT_RENDER(hdc, pos.x, pos.y, size.x, size.y);
    ComponentRender(hdc);
}

void EnemyBullet::EnterCollision(Collider* _other)
{
    cout << "Enter" << endl;
    if (_other->IsTrigger())
    {
        if (_other->GetName() == L"Player")
        {
            cout << "Enemy collided with DevObject. Destroying both." << endl;
            GET_SINGLE(SceneManager)->RequestDestroy(this);
            GET_SINGLE(SceneManager)->RequestDestroy(_other->GetOwner());
        }
    }
}
