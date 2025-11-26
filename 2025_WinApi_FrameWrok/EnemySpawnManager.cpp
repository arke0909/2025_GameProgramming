#include "pch.h"
#include "EnemySpawnManager.h"
#include "Enemy.h"
#include "SceneManager.h"
#include "Object.h"
#include "MeleeEnemy.h"
#include "RangedEnemy.h"



void EnemySpawnManager::Init()
{
    _mapWidth = 800.0f;
    _mapHeight = 600.0f;
    _spawnInterval = 2.0f;
    _elapsedTime = 0.0f;
}

void EnemySpawnManager::SetMapSize(float width, float height)
{
    _mapWidth = width;
    _mapHeight = height;
}

void EnemySpawnManager::Update()
{
    _elapsedTime += fDT;

    if (_elapsedTime >= _spawnInterval)
    {
        SpawnEnemy();
        _elapsedTime = 0.0f;
    }
}

void EnemySpawnManager::SpawnEnemy()
{
    Enemy * enemy = CreateRandomEnemy();
    
    srand((unsigned int)time(nullptr));

    float x = rand() % _mapWidth + 1;
    float y = rand() % _mapHeight + 1;

    Vec2 pos(x, y);
    Vec2 size(50.f, 50.f);

	enemy->SetPos(pos);
    //Spawn<Enemy>(Layer::ENEMY, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 }, { 100.f,100.f });
}

Enemy* EnemySpawnManager::CreateRandomEnemy()
{
    srand((unsigned int)time(nullptr));

    int type = rand() % 2;
	Enemy* enemy = nullptr;
    if (type == 0)
    {
        enemy = new MeleeEnemy();
        GET_SINGLE(SceneManager)->GetCurScene()
            ->AddObject(enemy, Layer::ENEMY);
    }
    else
    {
        enemy = new RangedEnemy();
        GET_SINGLE(SceneManager)->GetCurScene()
            ->AddObject(enemy, Layer::ENEMY);
    }
	return enemy;
}