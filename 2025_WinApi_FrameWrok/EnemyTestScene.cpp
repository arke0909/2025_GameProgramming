#include "pch.h"
#include "EnemyTestScene.h"
#include "CollisionManager.h"
#include "EnemySpawnManager.h"
#include "Player.h"

void EnemyTestScene::Init()
{
	Player* player;
	AddObject(player = new Player, Layer::PLAYER);
	player->SetPos({ WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
	player->SetSize({ 75, 75 });


	_spawn = GET_SINGLE(EnemySpawnManager);
	_spawn->Init(player);
	_spawn->SetMapSize((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
}

void EnemyTestScene::Update()
{
	Scene::Update();
	_spawn->Update();
}
