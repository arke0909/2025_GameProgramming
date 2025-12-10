#include "pch.h"
#include "EnemySpawnManager.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "MeleeEnemy.h"
#include "RangedEnemy.h"
#include "EnemyBoss.h"
#include "ArmorEnemy.h"
#include "CircleShotEnemy.h"
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

    _mapWidth = SCREEN_WIDTH;
    _mapHeight = SCREEN_HEIGHT;

    _waveDelay = 2.f;
    _noSpawnDistance = 150.f;

    _currentWave = 0;
    _waveActive = false;
    _waveDelayTimer = 0.f;

    _waves = {
        // 1 wave
        {{ {EnemyType::Melee, 6} }},

        // 2 wave
        {{ {EnemyType::Melee, 5}, {EnemyType::Ranged, 2} }},

        // 3 wave
        {{ {EnemyType::Melee, 6}, {EnemyType::Ranged, 4} }},

        // 4 wave
        {{ {EnemyType::Ranged, 6}, {EnemyType::Fast, 3} }},

        // 5 wave
        {{ {EnemyType::Armor, 3}, {EnemyType::Melee, 5} }},

        // 6 wave
        {{ {EnemyType::Fast, 5}, {EnemyType::Ranged, 4} }},

        // 7 wave
        {{ {EnemyType::CircleShot, 2}, {EnemyType::Fast, 4}, {EnemyType::Melee, 4} }},

        // 8 wave
        {{ {EnemyType::Melee, 5}, {EnemyType::Ranged, 4}, {EnemyType::Nonemove, 2} }},

        // 9 wave
        {{ {EnemyType::CircleShot, 3}, {EnemyType::Fast, 4}, {EnemyType::Nonemove, 3} }},

        // boss
        {{ {EnemyType::Melee, 0} }}
    };


    GET_SINGLE(GameManager)->currentWavwe = _currentWave + 1;
}

void EnemySpawnManager::Update()
{
    UpdateWave();
}

float EnemySpawnManager::GetWaveHPMultiplier() const
{
    return 1.0f + (_currentWave * 0.2f);
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

    if (_spawning)
    {
        _spawnTimer += fDT;
        if (_spawnTimer >= _spawnCoolTime)
        {
            _spawnTimer = 0.f;

            if (!_spawnQueue.empty())
            {
                SpawnEnemy(_spawnQueue.front());
                _spawnQueue.pop();
            }
            else
            {
                _spawning = false;
            }
        }
    }

    if (!_spawning && _spawnedEnemies.empty())
    {
        if (_currentWave < (int)_waves.size() - 1)
        {
            _currentWave++;
            GET_SINGLE(GameManager)->currentWavwe = _currentWave + 1;
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

    while (!_spawnQueue.empty())
        _spawnQueue.pop();

    for (auto& info : _waves[_currentWave].enemies)
    {
        for (int i = 0; i < info.second; i++)
            _spawnQueue.push(info.first);
    }

    _spawning = true;
    _spawnTimer = 0.f;
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

        float hpMul = GetWaveHPMultiplier();
        e->GetComponent<EntityHealthComponent>()->ApplyHPScale(hpMul);

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

    float hpMul = GetWaveHPMultiplier();
    e->GetComponent<EntityHealthComponent>()->ApplyHPScale(hpMul);

    GET_SINGLE(SceneManager)->GetCurScene()->AddObject(e, Layer::ENEMY);

    _spawnedEnemies.push_back(e);
}


Enemy* EnemySpawnManager::CreateEnemy(EnemyType type)
{
    switch (type)
    {
    case EnemyType::Melee:
        return new MeleeEnemy();
        break;
    case EnemyType::Ranged:
        return new RangedEnemy();
        break;
    case EnemyType::Armor:
        return new ArmorEnemy();
        break;
    case EnemyType::Fast:
        return new FastEnemy();
        break;
    case EnemyType::Nonemove:
        return new NoneMoveEnemy();
        break;
    case EnemyType::CircleShot:
        return new CircleShotEnemy();
        break;
    default:
        break;
    }

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

    float x = 0.f;
    float y = 0.f;

    if (side == 0)
    {
        x = static_cast<float>(rand() % (_mapWidth - _spawnMargin * 2) + _spawnMargin);
        y = static_cast<float>(_spawnMargin);
    }
    else if (side == 1)
    {
        x = static_cast<float>(rand() % (_mapWidth - _spawnMargin * 2) + _spawnMargin);
        y = static_cast<float>(_mapHeight - _spawnMargin);
    }
    else if (side == 2)
    {
        x = static_cast<float>(_spawnMargin);
        y = static_cast<float>(rand() % (_mapHeight - _spawnMargin * 2) + _spawnMargin);
    }
    else
    {
        x = static_cast<float>(_mapWidth - _spawnMargin);
        y = static_cast<float>(rand() % (_mapHeight - _spawnMargin * 2) + _spawnMargin);
    }

    return Vec2(x, y);
}

void EnemySpawnManager::DeadEnemy(Enemy* enemy)
{
    auto it = std::find(_spawnedEnemies.begin(), _spawnedEnemies.end(), enemy);
    if (it != _spawnedEnemies.end())
    {
        _spawnedEnemies.erase(it);
        enemy->SetDead();
		GET_SINGLE(GameManager)->coin += enemy->GetDropGold();
        GET_SINGLE(SceneManager)->RequestDestroy(enemy);
    }
}
