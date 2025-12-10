#include "pch.h"
#include "GameScene.h"
#include "CollisionManager.h"
#include "WindowManager.h"
#include "UIManager.h"
#include "UIImage.h"
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
#include "EnemySpawnManager.h"
#include "GameWindow.h"
#include "StoreUI.h"
#include "GameEvent.h"

void GameScene::Init()
{
	_inGameWindow = GET_SINGLE(WindowManager)
		->CreateSubWindow<GameWindow>(
			L"InGame",
			{
				{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2},
				{400,400}
			});
	GET_SINGLE(WindowManager)
		->CreateSubWindow<GameWindow>(
			L"Temp",
			{
				{SCREEN_WIDTH / 2 - 500, SCREEN_HEIGHT / 2},
				{400,400}
			});

    _informationWindow = GET_SINGLE(WindowManager)->CreateSubWindow<Window>(
        L"Information", { {SCREEN_WIDTH - 300, SCREEN_HEIGHT / 2 - 150}, {120, 85} });

    _storeWindow = GET_SINGLE(WindowManager)->CreateSubWindow<Window>
    (L"Store", { {SCREEN_WIDTH - 300,SCREEN_HEIGHT / 2 + 150},{500,300} });

    GameEvents::OnItemPurchased.Subscribe([](const ItemInfo& item) 
        {
            MessageBox(nullptr, L"구매 완료!", L"구매", MB_OK);
        });

    SubUIManager* inGameUI = _inGameWindow->GetUI();
    SubUIManager* infoUI = _informationWindow->GetUI();
    SubUIManager* storeUI = _storeWindow->GetUI();
    StoreUI* shop = new StoreUI({ 250, 150 }, { 500, 300 });
    storeUI->Add(shop);

    GET_SINGLE(GameManager)->storeWindowHandle = _storeWindow->GetHandle();

    WaveLabel* waveLabel = new WaveLabel({ 200, 20 }, { 200, 50 }, FontType::UI);
    inGameUI->Add(waveLabel);

    CoinLabel* coinLabel = new CoinLabel({ 50, 20 }, { 200, 50 }, FontType::UI);
    inGameUI->Add(coinLabel);

    Texture* hpTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Heart");

	UIImage* heart = new UIImage(hpTexture, { 45, 40 }, {80,80 });
	infoUI->Add(heart);

    HpLabel* hpLabel = new HpLabel({ 100, 40 }, { 100, 30 }, FontType::UI);

	infoUI->Add(hpLabel);

    auto* player = Spawn<Player>(Layer::PLAYER, _inGameWindow->GetPos(), { 75, 75 });
    player->SetWindow(_inGameWindow);

    _spawn = GET_SINGLE(EnemySpawnManager);
    _spawn->Init(player);

    WallSet wallSets[4] = { {false,false}, {false,true}, {true,false}, {true,true} };
    for (int i = 0; i < 4; ++i)
    {
        auto* wall = new Wall(_inGameWindow);
        wall->SetWall(wallSets[i]);
        AddObject(wall, Layer::WALL);
    }


    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::PLAYER);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PROJECTILE, Layer::WALL);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::BULLET, Layer::WALL);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::BULLET, Layer::ENEMY);
    GET_SINGLE(CollisionManager)->CheckLayer(Layer::PLAYER, Layer::DEFAULT);
}

void GameScene::Update()
{
    Scene::Update();
    _spawn->Update();

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

    if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::TAB))
    {
        _storeVisible = !_storeVisible;
        _storeWindow->SetVisible(_storeVisible);
    }
}
