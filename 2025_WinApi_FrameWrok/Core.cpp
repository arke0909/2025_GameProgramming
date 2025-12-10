#include "pch.h"
#include "Core.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"
#include "WindowManager.h"
#include "UIManager.h"

bool Core::Init(HWND hWnd, HINSTANCE hInstance)
{
	_hWnd = hWnd;
	_hInstance = hInstance;
	_hdc = ::GetDC(_hWnd);
	_hBackBit = 0;
	_hBackDC = 0;

	// 더블버퍼링
	// 1. 생성
	_hBackBit = ::CreateCompatibleBitmap(_hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	_hBackDC = ::CreateCompatibleDC(_hdc);

	// 2. 연결
	::SelectObject(_hBackDC, _hBackBit);

	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init();
	if (!GET_SINGLE(ResourceManager)->Init())
		return false;
	GET_SINGLE(SceneManager)->Init();

	return true;
}

void Core::GameLoop()
{
	MainUpdate();
	MainRender();
	GET_SINGLE(SceneManager)->GetCurScene()->FlushEvent();
}

void Core::CleanUp()
{
	::DeleteObject(_hBackBit);
	::DeleteDC(_hBackDC);
	::ReleaseDC(_hWnd, _hdc);
	GET_SINGLE(ResourceManager)->Release();
}

void Core::MainUpdate()
{
	GET_SINGLE(TimeManager)->Update();
	{
		static float accmulator = 0.f;
		const float fixedDT = 1.f / 60.f;
		accmulator += fDT;
		while (accmulator >= fixedDT)
		{
			GET_SINGLE(SceneManager)->FixedUpdate(fixedDT);
			GET_SINGLE(CollisionManager)->Update();
			accmulator -= fixedDT;
		}
	}
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(ResourceManager)->FmodUpdate();
	GET_SINGLE(SceneManager)->Update();
	GET_SINGLE(UIManager)->Update();
	GET_SINGLE(WindowManager)->Update();
}


void Core::MainRender()
{
	::PatBlt(_hBackDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLACKNESS);

	GET_SINGLE(SceneManager)->Render(_hBackDC);

	GET_SINGLE(UIManager)->Render(_hBackDC);

	GET_SINGLE(WindowManager)->Render(_hBackDC);

	::BitBlt(_hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, _hBackDC, 0, 0, SRCCOPY);
}

