#include "pch.h"
#include "EnemySpawnManager.h"
#include "Enemy.h"
#include "SceneManager.h"
#include "Object.h"
#include "MeleeEnemy.h"
#include "RangedEnemy.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void EnemySpawnManager::Init(Player* player)
{
    _player = player;

    srand(unsigned int(time(nullptr)));

    _spawnInterval = 3.0f;
    _elapsedTime = 0.0f;
}

void EnemySpawnManager::SetMapSize(float width, float height)
{
    _mapWidth = static_cast<int>(width);
    _mapHeight = static_cast<int>(height);
}

void EnemySpawnManager::Update()
{
    _elapsedTime += fDT;

    while (_elapsedTime >= _spawnInterval)
    {
        SpawnEnemy();
        _elapsedTime -= _spawnInterval;
    }
}

void EnemySpawnManager::SpawnEnemy()
{
    Enemy* enemy = CreateRandomEnemy();

    // 랜덤 위치 계산, 윈도우 범위 안
    float x = rand() % _mapWidth;
    float y = rand() % _mapHeight;

    Vec2 pos(x, y);
    Vec2 size(50.f, 50.f);

    enemy->SetPos(pos);
    enemy->SetSize(size);
}

Enemy* EnemySpawnManager::CreateRandomEnemy()
{
    int type = rand() % 2;
    Enemy* enemy = nullptr;

    if (type == 0)
    {
        enemy = new MeleeEnemy();
    }
    else
    {
        enemy = new RangedEnemy();
    }

    enemy->SetTarget(_player);

    GET_SINGLE(SceneManager)->GetCurScene()->AddObject(enemy, Layer::ENEMY);

    return enemy;
}
