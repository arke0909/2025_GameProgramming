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
		L"GameOver", { {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {500,500} });

	Texture* gameOverTexture = GET_SINGLE(ResourceManager)->GetTexture(L"GameOver");
	Texture* buttonTexture = GET_SINGLE(ResourceManager)->GetTexture(L"Button");

	UIImage* gameOverImage = new UIImage(gameOverTexture, { 250, 200 }, { 400, 200 });

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

	SubUIManager* gameOverUI = _gameOverWIndow->GetUI();
	gameOverUI->Add(gameOverImage);
	gameOverUI->Add(restartButton);
	gameOverUI->Add(exitButton);
}
