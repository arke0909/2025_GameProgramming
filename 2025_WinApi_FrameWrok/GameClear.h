#pragma once
#include "Scene.h"

class Window;

class GameClear :
	public Scene
{
public:
	void Init() override;

private:
	Window* _gameClearWIndow = nullptr;
};

