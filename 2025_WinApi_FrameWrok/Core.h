#pragma once
#include"pch.h"

class Core
{
	DECLARE_SINGLE(Core);
public:
	bool Init(HWND hWnd);
	void GameLoop();
	void CleanUp();
public:
	const HDC& GetMainDC() const { return _hdc; }
	const HWND& GetHwnd() const { return _hWnd; }
private:
	void MainUpdate();
	void MainRender();
private:
	HDC _hdc;
	HWND _hWnd;
	
	HBITMAP _hBackBit;
	HDC _hBackDC;
};

