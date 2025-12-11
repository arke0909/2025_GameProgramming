#pragma once
#include "Scene.h"

class Window;
class GameOverUI  : 
	public Scene
{
	public:
		void Init() override;

private:
	Window* _gameOverWIndow = nullptr;
};

