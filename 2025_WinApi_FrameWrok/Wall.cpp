#include "pch.h"
#include "Wall.h"
#include "GameWindow.h"
#include "BoxCollider.h"
#include "Rigidbody.h"
#include "Projectile.h"
#include "WallForceObject.h"

Wall::Wall(GameWindow* inGameWindow)
{
	_inGameWindow = inGameWindow;
	boxCol = AddComponent<BoxCollider>();
	boxCol->SetName(L"Wall");
	boxCol->SetTrigger(false);
}

Wall::~Wall()
{
}

void Wall::Update()
{
	int w = _inGameWindow->GetWindowSize().x;
	int h = _inGameWindow->GetWindowSize().y;
	Vec2 size =
		(_wallSet.isVertical
			? Vec2{ 1, h }
	: Vec2{ w, 1 });

	Vec2 windowPos = GET_LT(_inGameWindow->GetSize(), _inGameWindow->GetPos());

	float x = _wallSet.isStart ? 0 : w;
	float y = _wallSet.isStart ? 0 : h;

	if (_wallSet.isVertical)
	{
		y = h * 0.5;
	}
	else
	{
		x = w * 0.5;
	}

	x += windowPos.x;
	y += windowPos.y;

	boxCol->SetSize(size);
	_pos = { x,y };
}

void Wall::Render(HDC hdc)
{
	GDISelector pen(hdc, MyPenType::WHITE);
	ComponentRender(hdc);
}

void Wall::EnterCollision(Collider* _other)
{
	auto* rigidbody = _other->GetOwner()->GetComponent<Rigidbody>();
	
	if (rigidbody)
	{
		auto* proj = dynamic_cast<WallForceObject*>(_other->GetOwner());
		float wallForce = proj->GetWallForce();
		Vec2 velocity = rigidbody->GetVelocity();
		velocity.Normalize();

		Vec2 addPos = velocity * wallForce;

		if (!_wallSet.isStart)
			addPos *= 2;

		_inGameWindow->
			WindowMoveAndChangeSize(addPos
				, {::abs(velocity.x * wallForce),
				::abs(velocity.y * wallForce)
				});
	}
}

void Wall::StayCollision(Collider* _other)
{
}

void Wall::ExitCollision(Collider* _other)
{
}
