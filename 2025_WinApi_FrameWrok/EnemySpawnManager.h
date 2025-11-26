#pragma once
#include "Enemy.h"
class EnemySpawnManager
{
public:
    EnemySpawnManager();
    ~EnemySpawnManager();

    void Update();
    void SetMapSize(float width, float height);

private:
    void SpawnEnemy();
    Enemy* CreateRandomEnemy();

private:
    float _mapWidth;
    float _mapHeight;
    float _spawnInterval;
    float _elapsedTime;
};

