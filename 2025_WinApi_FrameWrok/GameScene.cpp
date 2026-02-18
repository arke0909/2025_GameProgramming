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
#include "SceneManager.h"

void GameScene::Init()
{
    GET_SINGLE(GameManager)->ResetGame();

    _inGameWindow = GET_SINGLE(WindowManager)->CreateSubWindow<GameWindow>(
        L"InGame",
        { {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {400, 400} }
    );

    _informationWindow = GET_SINGLE(WindowManager)->CreateSubWindow<Window>(
        L"Information", { {SCREEN_WIDTH - 500, 300.0f }, {120, 85} });

    _storeWindow = GET_SINGLE(WindowManager)->CreateSubWindow<Window>(
        L"Store", { {SCREEN_WIDTH - 300, SCREEN_HEIGHT / 2 + 150}, {500, 300} });

    SubUIManager* inGameUI = _inGameWindow->GetUI();
    SubUIManager* infoUI = _informationWindow->GetUI();
    SubUIManager* storeUI = _storeWindow->GetUI();


    auto shop = std::make_unique<StoreUI>(Vec2{ 250, 150 }, Vec2{ 500, 300 });
    storeUI->Add(std::move(shop));

    GET_SINGLE(GameManager)->storeWindowHandle = _storeWindow->GetHandle();


    auto waveLabel = std::make_unique<WaveLabel>(Vec2{ 200, 20 }, Vec2{ 200, 50 }, FontType::UI);
    inGameUI->Add(std::move(waveLabel));


    auto coinLabel = std::make_unique<CoinLabel>(Vec2{ 50, 20 }, Vec2{ 200, 50 }, FontType::UI);
    inGameUI->Add(std::move(coinLabel));


    Texture* hpTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Heart");
    auto heartImage = std::make_unique<UIImage>(hpTexture, Vec2{ 45, 40 }, Vec2{ 60, 60 });
    infoUI->Add(std::move(heartImage));


    auto hpLabel = std::make_unique<HpLabel>(Vec2{ 100, 40 }, Vec2{ 100, 30 }, FontType::UI);
    infoUI->Add(std::move(hpLabel));


    auto* player = Spawn<Player>(Layer::PLAYER, _inGameWindow->GetPos(), Vec2{ 75, 75 });
    player->SetWindow(_inGameWindow);


    _spawn = GET_SINGLE(EnemySpawnManager);
    _spawn->Init(player);


    WallSet wallSets[4] = {
        {false, false},
        {false, true},
        {true, false},
        {true, true}
    };

    for (int i = 0; i < 4; ++i)
    {
        auto* wall = new Wall(_inGameWindow); 
        wall->SetWall(wallSets[i]);
        AddObject(wall, Layer::WALL);
    }


    auto* cm = GET_SINGLE(CollisionManager);
    cm->CheckLayer(Layer::PROJECTILE, Layer::ENEMY);
    cm->CheckLayer(Layer::BULLET, Layer::ENEMY);
    cm->CheckLayer(Layer::BULLET, Layer::PLAYER);
    cm->CheckLayer(Layer::PROJECTILE, Layer::PLAYER);
    cm->CheckLayer(Layer::PROJECTILE, Layer::WALL);
    cm->CheckLayer(Layer::BULLET, Layer::WALL);
    cm->CheckLayer(Layer::PLAYER, Layer::DEFAULT);

    _storeWindow->SetVisible(false);
}


void GameScene::Update()
{
    Scene::Update();
    _spawn->Update();

    if (GET_SINGLE(GameManager)->playerHealth <= 0)
    {
        GET_SINGLE(SceneManager)->LoadScene(L"GameOver");
        return;
    }

    if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::R))
    {
        GET_SINGLE(GameManager)->coin += 10000;
    }

    if (GET_SINGLE(InputManager)->IsDown(KEY_TYPE::TAB))
    {
        _storeVisible = !_storeVisible;
        GET_SINGLE(TimeManager)->SetTimeScale(_storeVisible ? 0 : 1);
        _storeWindow->SetVisible(_storeVisible);
    }
}

void GameScene::Render(HDC hdc)
{
	Scene::Render(hdc);
	Graphics graphics(hdc);
	RenderWindowEdge(graphics);

}

void GameScene::RenderWindowEdge(Graphics& graphics)
{
    // 윈도우 작업바를 포함한 사이즈
	Vec2 winSize = _inGameWindow->GetSize();
    // 작업바를 포함하지 않은 사이즈
    Vec2 winRectSize = _inGameWindow->GetWindowSize();

    // 작업바를 포함해서 사이즈 기준으로 계산한 윈도우의 위치
	Vec2 winPos = _inGameWindow->GetPos();
    for(int i = 1; i <= _windowAreaPixel; ++i)
    {
        float alpha = std::lerp(0, 255, (float)((_windowAreaPixel - i) / _windowAreaPixel));
        Pen pen(Color(alpha, 255, 255, 255));

        // winPos는 작업바를 포함해 계산한 위치이므로 작업바를 포함한 사이즈의 좌상단
		int x = winPos.x - winSize.x / 2 + i;
        int y = winPos.y - winSize.y / 2 + i;

        // right, bottom은 좌상단 기준 작업바를 포함하지 않은 사이즈만큼의 크기이므로 차이만큼 빼주기
        Rect rt = {
        x, y,
        (int)(winRectSize.x) - i * 2,
        (int)(winRectSize.y) - i * 2 };

        graphics.DrawRectangle(&pen, rt);
	}
}
