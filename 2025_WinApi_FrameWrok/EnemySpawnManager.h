#pragma once
#include "Enemy.h"
class EnemySpawnManager
{
    DECLARE_SINGLE(EnemySpawnManager);
public:
    void Init();
    void Update();
    void SetMapSize(float width, float height);
    void SpawnEnemy();

private:
    Enemy* CreateRandomEnemy();

private:
    int _mapWidth;
    int _mapHeight;
    float _spawnInterval;
    float _elapsedTime;
};
