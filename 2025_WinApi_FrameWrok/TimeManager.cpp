#include "pch.h"
#include "TimeManager.h"
#include "Core.h"
#include "InputManager.h"

void TimeManager::Init()
{
	// 현재 카운트의 틱을 가져온다.
	::QueryPerformanceCounter(&_llPrevCnt);

	// 초당 카운트를 1000만을 반환
	::QueryPerformanceFrequency(&_llFrequency);
}

void TimeManager::Update()
{
	::QueryPerformanceCounter(&_llCurCnt);
	_deltaTime = (float)(_llCurCnt.QuadPart - _llPrevCnt.QuadPart)
		/ (float)_llFrequency.QuadPart;
	_llPrevCnt = _llCurCnt;

	_frameCnt++;
	_frameTime += _deltaTime;

	if (_frameTime >= 1.f)
	{
		_fps = (UINT)(_frameCnt / _frameTime);
		_frameTime = 0.f;
		_frameCnt = 0;
		//wstring strDt = std::to_wstring(_deltaTime);
		//wstring strFps = std::to_wstring(_fps);
		//wstring str = L"FPS: " + strFps + L" DT: " + strDt;
		//::TextOut(GET_SINGLE(Core)->GetMainDC(), 0, 0, str.c_str(), str.length());
		POINT mousePos = GET_MOUSEPOS;
		wstring str = std::format(L"FPS: {0}, DT: {1:.6f}, Mouse: {2}, {3}", _fps, _deltaTime, mousePos.x, mousePos.y);
		::SetWindowText(GET_SINGLE(Core)->GetHwnd(), str.c_str());
	}
}
