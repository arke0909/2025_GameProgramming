#include "pch.h"
#include "GameScene.h"
#include "CollisionManager.h"
#include "WindowManager.h"
#include "UIManager.h"
#include "UILabel.h"
#include "Player.h"
#include "GameManager.h"
#include "Wall.h"
#include "Window.h"
#include "WaveLabel.h"
#include "HPImage.h"
#include "CoinLabel.h"
#include "InputManager.h"
#include "ResourceManager.h"

void GameScene::Init()
{
    _inGameWindow = GET_SINGLE(WindowManager)->CreateSubWindow(
        L"InGame", { {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {400, 400} });

    _informationWindow = GET_SINGLE(WindowManager)->CreateSubWindow(
        L"Information", { {SCREEN_WIDTH - 300, SCREEN_HEIGHT / 2 - 150}, {400, 85} });

    _storeWindow = GET_SINGLE(WindowManager)->CreateSubWindow
    (L"Store", { {SCREEN_WIDTH - 300,SCREEN_HEIGHT / 2 + 150},{500,300} });

    SubUIManager* inGameUI = _inGameWindow->GetUI();
    SubUIManager* infoUI = _informationWindow->GetUI();

    WaveLabel* waveLabel = new WaveLabel({ 200, 20 }, { 200, 50 }, FontType::TITLE);
    inGameUI->Add(waveLabel);

    CoinLabel* coinLabel = new CoinLabel({ 50, 20 }, { 200, 50 }, FontType::TITLE);
    inGameUI->Add(coinLabel);


    UILabel* hpLabel = new UILabel(L"HP:", { 20, 40 }, { 100, 30 }, FontType::TITLE);
    infoUI->Add(hpLabel);

    const int maxHP = 5;
    const int iconSize = 40;
    const int spacing = 10;
    Texture* hpTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Heart");

    for (int i = 0; i < maxHP; ++i)
    {
        Vec2 pos = { 60 + i * (iconSize + spacing), 40 };
        HPImage* heart = new HPImage(pos, { iconSize, iconSize }, hpTexture);
        _hearts.push_back(heart);
        infoUI->Add(heart);
    }

    int playerPosX = _inGameWindow->GetPos().x + _inGameWindow->GetSize().x / 2;
    int playerPosY = _inGameWindow->GetPos().y + _inGameWindow->GetSize().y / 2;

    auto* player = Spawn<Player>(Layer::PLAYER, { playerPosX, playerPosY }, { 75, 75 });
    player->SetWindow(_inGameWindow);


    WallSet wallSets[4] = { {false,false}, {false,true}, {true,false}, {true,true} };
    for (int i = 0; i < 4; ++i)
    {
        auto* wall = new Wall(_inGameWindow);
        wall->SetWall(wallSets[i]);
        AddObject(wall, Layer::WALL);
    }


    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::PLAYER);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::WALL);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
}

void GameScene::Update()
{
    Scene::Update();


    if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::F))
    {
        GET_SINGLE(GameManager)->currentWavwe++;
    }

    if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::R))
    {
        GET_SINGLE(GameManager)->coin += 100;
    }

    if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::Q))
    {
        if (GET_SINGLE(GameManager)->playerHealth > 0)
            GET_SINGLE(GameManager)->playerHealth++;
    }

    int curHP = GET_SINGLE(GameManager)->playerHealth;
    for (int i = 0; i < _hearts.size(); ++i)
    {
        _hearts[i]->SetVisible(i < curHP);
    }
}
