#include "pch.h"
#include "EnemySpawnManager.h"
#include "SceneManager.h"
#include "MeleeEnemy.h"
#include "RangedEnemy.h"
#include "EnemyBoss.h"
#include "ArmorEnemy.h"
#include "FastEnemy.h"
#include "NoneMoveEnemy.h"
#include "WindowManager.h"
#include "Window.h"
#include <cstdlib>
#include <ctime>

void EnemySpawnManager::Init(Player* player)
{
    _player = player;

    srand(unsigned int(time(nullptr)));

    _mapWidth = WINDOW_WIDTH;
    _mapHeight = WINDOW_HEIGHT;

    _waveDelay = 2.f;
    _noSpawnDistance = 150.f;

    _currentWave = 0;
    _waveActive = false;
    _waveDelayTimer = 0.f;

    _waves = {
        { { {EnemyType::Nonemove, 1}, {EnemyType::Melee, 1} } },
        { { {EnemyType::Nonemove, 4}, {EnemyType::Ranged, 2} } },
        { { {EnemyType::Ranged, 6} } },
        { { {EnemyType::Melee, 4}, {EnemyType::Armor, 2} } },
        { { {EnemyType::Melee, 6} } },
        { { {EnemyType::Melee, 3}, {EnemyType::Ranged, 3}, {EnemyType::Armor, 2} } },
        { { {EnemyType::Melee, 4}, {EnemyType::Ranged, 4}, {EnemyType::Melee, 2} } },
        { { {EnemyType::Armor, 4}, {EnemyType::Melee, 4} } },
        { { {EnemyType::Melee, 5}, {EnemyType::Ranged, 5}, {EnemyType::Armor, 5} } },
        { { {EnemyType::Melee, 0} } }
    };
}

void EnemySpawnManager::Update()
{
    UpdateWave();
}

void EnemySpawnManager::UpdateWave()
{
    if (_gameClear)
        return;

    if (!_waveActive)
    {
        _waveDelayTimer += fDT;
        if (_waveDelayTimer >= _waveDelay)
        {
            _waveDelayTimer = 0.f;
            _waveActive = true;
            TrySpawnWave();
        }
        return;
    }

    if (_spawnedEnemies.empty())
    {
        if (_currentWave < (int)_waves.size() - 1)
        {
            _currentWave++;
            _waveActive = false;
        }
        else
        {
            _waveActive = false;
            _gameClear = true;
        }
    }
}

void EnemySpawnManager::TrySpawnWave()
{
    if (_currentWave == _waves.size() - 1)
    {
        EnemyBoss* e = new EnemyBoss();

        e->SetTarget(_player);
        e->SetPos({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 });
        e->CreateEnemyWindow();

        _spawnedEnemies.push_back(e);
        GET_SINGLE(SceneManager)->GetCurScene()->AddObject(e, Layer::ENEMY);
        return;
    }

    for (auto& info : _waves[_currentWave].enemies)
    {
        for (int i = 0; i < info.second; i++)
            SpawnEnemy(info.first);
    }
}


void EnemySpawnManager::SpawnEnemy(EnemyType type)
{
    if (type == EnemyType::Nonemove) {
        NoneMoveEnemy* e = new NoneMoveEnemy();
        Vec2 pos;
        float fx = static_cast<float>(rand()) / RAND_MAX;
        float fy = static_cast<float>(rand()) / RAND_MAX;
        pos.x = fx * _mapWidth;
        pos.y = fy * _mapHeight;

        e->SetPos(pos);
        e->SetTarget(_player);
        e->CreateEnemyWindow();
        GET_SINGLE(SceneManager)->GetCurScene()->AddObject(e, Layer::ENEMY);
        _spawnedEnemies.push_back(e);
        return;
    }

    Vec2 pos;

    if (!FindSpawnPosition(pos))
        return;

    Enemy* e = CreateEnemy(type);

    e->SetPos(pos);
    e->SetTarget(_player);

    GET_SINGLE(SceneManager)->GetCurScene()->AddObject(e, Layer::ENEMY);

    _spawnedEnemies.push_back(e);
}


Enemy* EnemySpawnManager::CreateEnemy(EnemyType type)
{
    if (type == EnemyType::Melee) 
        return new MeleeEnemy();

    if (type == EnemyType::Ranged)
        return new RangedEnemy();

    if (type == EnemyType::Armor)
        return new ArmorEnemy();

    if (type == EnemyType::Nonemove)
        return new NoneMoveEnemy();

    return nullptr;
}

bool EnemySpawnManager::FindSpawnPosition(Vec2& outPos)
{
    for (int i = 0; i < 10; i++)
    {
        Vec2 cand = GenerateEdgePosition();
        if (IsPositionValid(cand))
        {
            outPos = cand;
            return true;
        }
    }
    return false;
}

bool EnemySpawnManager::IsPositionValid(const Vec2& pos)
{
	Vec2 playerPos = _player->GetPos();
    if ((playerPos - pos).Length() < _noSpawnDistance)
        return false;

    auto enemies = _spawnedEnemies;
    for (auto e : enemies)
    {
		Vec2 enemyPos = e->GetPos();
        if ((enemyPos - pos).Length() < _noSpawnDistance)
            return false;
    }
    return true;
}

Vec2 EnemySpawnManager::GenerateEdgePosition()
{
    int side = rand() % 4;

    if (side == 0)
        return Vec2((float)(rand() % _mapWidth), 0.f);

    if (side == 1)
        return Vec2((float)(rand() % _mapWidth), (float)_mapHeight);

    if (side == 2)
        return Vec2(0.f, (float)(rand() % _mapHeight));

    return Vec2((float)_mapWidth, (float)(rand() % _mapHeight));
}

void EnemySpawnManager::DeadEnemy(Enemy* enemy)
{
    auto it = std::find(_spawnedEnemies.begin(), _spawnedEnemies.end(), enemy);
    if (it != _spawnedEnemies.end())
    {
        _spawnedEnemies.erase(it);
        enemy->SetDead();
        GET_SINGLE(SceneManager)->RequestDestroy(enemy);
    }
}
