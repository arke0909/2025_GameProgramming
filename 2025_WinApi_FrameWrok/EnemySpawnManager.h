#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Window.h"
#include <vector>
#include <utility>

enum class EnemyType
{
    Melee,
    Ranged,
    Armor,
    Bounce,
    Nonemove
};

class EnemySpawnManager
{
    DECLARE_SINGLE(EnemySpawnManager);
public:
    void Init(Player* player);
    void Update();
    void DeadEnemy(Enemy* enemy);

private:
    struct WaveData
    {
        std::vector<std::pair<EnemyType, int>> enemies;
    };

    void UpdateWave();
    void TrySpawnWave();
    void SpawnEnemy(EnemyType type);
    Enemy* CreateEnemy(EnemyType type);
    bool FindSpawnPosition(Vec2& outPos);
    bool IsPositionValid(const Vec2& pos);
    Vec2 GenerateEdgePosition();

private:
    std::vector<Enemy*> _spawnedEnemies;
    Player* _player;
    std::vector<WaveData> _waves;
    int _currentWave;
    bool _waveActive;
    float _waveDelayTimer;

    int _mapWidth;
    int _mapHeight;

    float _waveDelay;
    float _noSpawnDistance;
    bool _gameClear = false;

};
