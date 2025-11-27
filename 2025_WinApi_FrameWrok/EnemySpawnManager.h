#pragma once
#include "Enemy.h"
class EnemySpawnManager
{
    DECLARE_SINGLE(EnemySpawnManager);
public:
    void Init(Player* player);
    void Update();
    void SpawnEnemy();

private:
    Enemy* CreateRandomEnemy();

private:
    Player* _player;
    int _mapWidth;
    int _mapHeight;
    float _spawnInterval;
    float _elapsedTime;
};
