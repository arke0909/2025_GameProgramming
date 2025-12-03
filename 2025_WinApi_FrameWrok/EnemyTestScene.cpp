#include "pch.h"
#include "EnemyTestScene.h"
#include "CollisionManager.h"
#include "EnemySpawnManager.h"
#include "Player.h"
#include "Wall.h"

void EnemyTestScene::Init()
{
	Player* player;
	AddObject(player = new Player, Layer::PLAYER);
	player->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
	player->SetSize({ 75, 75 });

	WallSet wallSets[4] =
	{
		{false,false},
		{false,true},
		{true,false},
		{true,true}
	};

	for (int i = 0; i < 4; ++i)
	{
		auto* wall = new Wall();
		wall->SetWall(wallSets[i]);
		AddObject(wall, Layer::WALL);
	}

	_spawn = GET_SINGLE(EnemySpawnManager);
	_spawn->Init(player);

	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::WALL);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ENEMY);
}

void EnemyTestScene::Update()
{
	Scene::Update();
	_spawn->Update();
}
