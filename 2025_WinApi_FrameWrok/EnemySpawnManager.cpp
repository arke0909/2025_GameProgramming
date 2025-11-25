#include "pch.h"
#include "EnemySpawnManager.h"
#include "Enemy.h"
#include "SceneManager.h"
#include "Object.h"
#include "MeleeEnemy.h"
#include "RangedEnemy.h"


EnemySpawnManager::EnemySpawnManager() :
    _mapWidth(800.0f),
    _mapHeight(600.0f),
    _spawnInterval(2.0f),
    _elapsedTime(0.0f)
{
}

EnemySpawnManager::~EnemySpawnManager()
{
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
    Enemy* enemy = CreateRandomEnemy();
    if (!enemy)
        return;

    float x = rand() / RAND_MAX * _mapWidth;
    float y = rand() / RAND_MAX * _mapHeight;

    enemy->SetPos(Vec2(x, y));
    //Spawn<Enemy>(Layer::ENEMY, { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 }, { 100.f,100.f });
}

Enemy* EnemySpawnManager::CreateRandomEnemy()
{
    int type = rand() % 2;

    //if (type == 0)
        //return new MeleeEnemy();
    
        return new RangedEnemy();
}