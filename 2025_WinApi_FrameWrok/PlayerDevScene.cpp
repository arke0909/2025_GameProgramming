#include "pch.h"
#include "PlayerDevScene.h"
#include "CollisionManager.h"
#include "Player.h"

void PlayerDevScene::Init()
{
	Spawn<Player>(Layer::PLAYER
		,{ WINDOW_WIDTH / 2 ,WINDOW_HEIGHT / 2 }
	, {75, 75});

	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
}

void PlayerDevScene::Update()
{
	Scene::Update();
}


