#include "pch.h"
#include "GameScene.h"
#include "CollisionManager.h"
#include "WindowManager.h"
#include "Player.h"
#include "Wall.h"
#include "Window.h"

void GameScene::Init()
{
	_inGameWindow = GET_SINGLE(WindowManager)
		->CreateSubWindow(
			L"InGame",
			{
				{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
				{400,400}
			});
	GET_SINGLE(WindowManager)
		->CreateSubWindow(
			L"Temp",
			{
				{SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2},
				{400,400}
			});

	int playerPosX = _inGameWindow->GetPos().x + _inGameWindow->GetSize().x / 2;
	int playerPosY = _inGameWindow->GetPos().y + _inGameWindow->GetSize().y / 2;

	auto* player = Spawn<Player>(Layer::PLAYER
		, { playerPosX,playerPosY }
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
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::WALL);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);

}

void GameScene::Update()
{
	Scene::Update();
}