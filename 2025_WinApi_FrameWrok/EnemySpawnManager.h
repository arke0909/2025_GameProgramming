#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Window.h"
#include <vector>
#include <utility>
#include <queue>

enum class EnemyType
{
    Melee,
    Ranged,
    Armor,
    Fast,
    Nonemove,
    CircleShot
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

    float GetWaveHPMultiplier() const;
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

    std::queue<EnemyType> _spawnQueue;
    float _spawnCoolTime = 2.5f;
    float _spawnTimer = 0.f;
    bool _spawning = false;

    int _spawnMargin = 300;
};
