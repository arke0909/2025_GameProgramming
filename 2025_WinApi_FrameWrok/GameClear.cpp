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
		L"GameClear", { {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {500,500} });

	Texture* gameOverTexture = GET_SINGLE(ResourceManager)->GetTexture(L"GameClear");
	Texture* buttonTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Button");

	UIImage* gameClearImage = new UIImage(gameOverTexture, { 250, 200 }, { 400, 200 });

	UIButton* restartButton = new UIButton(L"처음부터", { 250, 350 }, { 200, 50 }, FontType::UI, buttonTexture);
	restartButton->SetOnClick([]()
		{
			GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
		});
	UIButton* exitButton = new UIButton(L"타이틀로", { 250, 450 }, { 200, 50 }, FontType::UI, buttonTexture);
	exitButton->SetOnClick([]()
		{
			GET_SINGLE(SceneManager)->LoadScene(L"TitleScene");
		});

	SubUIManager* gameClearUI = _gameClearWIndow->GetUI();
	gameClearUI->Add(gameClearImage);
	gameClearUI->Add(restartButton);
	gameClearUI->Add(exitButton);
}
