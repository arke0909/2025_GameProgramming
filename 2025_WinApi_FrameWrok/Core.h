#pragma once
#include"pch.h"

class Core
{
	DECLARE_SINGLE(Core);
public:
	bool Init(HWND hWnd, HINSTANCE hInstance);
	void GameLoop();
	void CleanUp();
public:
	const HDC& GetMainDC() const { return _hdc; }
	const HDC& GetBackDC() const { return _hBackDC; }
	const HWND& GetHwnd() const { return _hWnd; }
	const HINSTANCE& GetInstance() const { return _hInstance; }
private:
	void MainUpdate();
	void MainRender();
private:
	HDC _hdc;
	HINSTANCE _hInstance;
	HWND _hWnd;
	
	HBITMAP _hBackBit;
	HDC _hBackDC;
};

