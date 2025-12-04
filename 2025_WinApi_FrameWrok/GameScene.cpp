#include "pch.h"
#include "GameScene.h"
#include "CollisionManager.h"
#include "WindowManager.h"
#include "UIManager.h"
#include "UILabel.h"
#include "Player.h"
#include "GameManager.h"
#include "Wall.h"
#include "Window.h"

void GameScene::Init()
{
	Window* inGameWindow = _inGameWindow = GET_SINGLE(WindowManager)
		->CreateSubWindow(
			L"InGame",
			{
				{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
				{400,400}
			});

	Window* informationWindow = GET_SINGLE(WindowManager)
		->CreateSubWindow(
			L"Information",
			{
				{SCREEN_WIDTH - 200, SCREEN_HEIGHT / 2},
				{300,400}
			});

	SubUIManager* gameSceneUI = inGameWindow->GetUI();

	UILabel* waveLabel = new UILabel(L" Wave : " + std::to_wstring(GET_SINGLE(GameManager)->currentWavwe), {200, 20}, {100,50}, FontType::TITLE);

	gameSceneUI->Add(waveLabel);

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