#pragma once
class GameManager
{
	DECLARE_SINGLE(GameManager);
public:
	int currentWavwe = 1;
	int playerHealth = 5;
	int playerMaxHealth = 5;
	int coin = 0;
	HWND storeWindowHandle;
	void ResetGame()
	{
		currentWavwe = 1;
		playerHealth = 5;
		playerMaxHealth = 5;
		coin = 0;
	}
};

