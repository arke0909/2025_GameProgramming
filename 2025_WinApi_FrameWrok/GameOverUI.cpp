#include "pch.h"
#include "GameOverUI.h"
#include "WindowManager.h"
#include "UIImage.h"
#include "UIButton.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SubUIManager.h"
#include "Window.h"

void GameOverUI::Init()
{
    _gameOverWIndow = GET_SINGLE(WindowManager)->CreateSubWindow<Window>(
        L"GameOver",
        { {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {500, 500} }
    );

    Texture* gameOverTexture = GET_SINGLE(ResourceManager)->GetTexture(L"GameOver");
    Texture* buttonTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Button");

    auto gameOverImage = std::make_unique<UIImage>(
        gameOverTexture,
        Vec2{ 250, 200 },
        Vec2{ 400, 200 }
    );

    auto exitButton = std::make_unique<UIButton>(
        L"타이틀로",
        Vec2{ 250, 300 },
        Vec2{ 200, 50 },
        FontType::UI,
        buttonTexture
    );

    exitButton->SetOnClick([]()
        {
            GET_SINGLE(SceneManager)->LoadScene(L"TitleScene");
        });

    SubUIManager* gameOverUI = _gameOverWIndow->GetUI();
    gameOverUI->Add(std::move(gameOverImage));
    gameOverUI->Add(std::move(exitButton));
}

