#include "pch.h"
#include "GameClear.h"
#include "WindowManager.h"
#include "UIImage.h"
#include "UIButton.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SubUIManager.h"
#include "Window.h"


void GameClear::Init()
{
    _gameClearWIndow = GET_SINGLE(WindowManager)->CreateSubWindow<Window>(
        L"GameClear",
        { {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {500, 500} }
    );

    Texture* gameClearTexture = GET_SINGLE(ResourceManager)->GetTexture(L"GameClear");
    Texture* buttonTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Button");

    auto gameClearImage = std::make_unique<UIImage>(
        gameClearTexture,
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

    SubUIManager* gameClearUI = _gameClearWIndow->GetUI();
    gameClearUI->Add(std::move(gameClearImage));
    gameClearUI->Add(std::move(exitButton));
}

