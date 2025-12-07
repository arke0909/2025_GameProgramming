#include "pch.h"
#include "PlayerDevScene.h"
#include "CollisionManager.h"
#include "WindowManager.h"
#include "Player.h"
#include "Wall.h"
#include "GameWindow.h"
#include "Window.h"

void PlayerDevScene::Init()
{
	_inGameWindow = (GameWindow*)GET_SINGLE(WindowManager)
		->CreateSubWindow<GameWindow>(
			L"InGame",
			{
				{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
				{400,400}
			});
	GET_SINGLE(WindowManager)
		->CreateSubWindow<GameWindow>(
			L"Temp",
			{
				{SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2},
				{400,400}
			});

	auto* player = Spawn<Player>(Layer::PLAYER
		, _inGameWindow->GetPos()
	, { 75, 75 });

	player->SetWindow(_inGameWindow);

	WallSet wallSets[4] =
	{
		{false,false},
		{false,true},
		{true,false},
		{true,true}
	};

	for (int i = 0; i < 4; ++i)
	{
		auto* wall = new Wall(_inGameWindow);
		wall->SetWall(wallSets[i]);
		AddObject(wall, Layer::WALL);
	}

	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::WALL);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);

}

void PlayerDevScene::Update()
{
	Scene::Update();
}


