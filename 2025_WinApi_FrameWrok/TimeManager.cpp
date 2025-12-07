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

    float scaledDT = _deltaTime * _timeScale;

    _frameCnt++;
    _time += scaledDT;        
    _frameTime += scaledDT;

    if (_frameTime >= 1.f)
    {
        _fps = (UINT)(_frameCnt / _frameTime);
        _frameTime = 0.f;
        _frameCnt = 0;

        POINT mousePos = GET_MOUSEPOS;
        wstring str = std::format(
            L"FPS: {0}, DT: {1:.6f}, ScaledDT: {2:.6f}, TimeScale: {3}, Mouse: {4}, {5}",
            _fps, _deltaTime, scaledDT, _timeScale, mousePos.x, mousePos.y
        );
        ::SetWindowText(GET_SINGLE(Core)->GetHwnd(), str.c_str());
    }
}

