#include "pch.h"
#include "Wall.h"
#include "BoxCollider.h"

Wall::Wall()
{
	boxCol = AddComponent<BoxCollider>();
	boxCol->SetName(L"Wall");
	boxCol->SetTrigger(false);
}

Wall::~Wall()
{
}

void Wall::Update()
{
	Vec2 size =
		(_wallSet.isVertical
			? Vec2{ 1, WINDOW_HEIGHT }
	: Vec2{ WINDOW_WIDTH, 1 });

	float x = _wallSet.isStart ? 0 : WINDOW_WIDTH;
	float y = _wallSet.isStart ? 0 : WINDOW_HEIGHT;

	if (_wallSet.isVertical)
	{
		y = WINDOW_HEIGHT * 0.5;
	}
	else
	{
		x = WINDOW_WIDTH * 0.5;
	}

	boxCol->SetSize(size);
	_pos = { x,y };
}

void Wall::Render(HDC hdc)
{
}
