#include "pch.h"
#include "GameWindow.h"
#include "EasingManager.h"

#undef min

GameWindow::GameWindow(LPCWSTR windowName, const WindowSet& windowSet)
	: Window(windowName, windowSet)
{
	_targetSize = _size;
}

GameWindow::~GameWindow()
{
}

void GameWindow::Update()
{
    Window::Update();

    float dt = GET_SINGLE(TimeManager)->GetDeltaTime();

    _windowSize.x = std::clamp(_windowSize.x, 1.0f, (float)SCREEN_WIDTH);
    _windowSize.y = std::clamp(_windowSize.y, 1.0f, (float)SCREEN_HEIGHT);

    _targetSize.x = std::clamp(_targetSize.x, 1.0f, (float)SCREEN_WIDTH);
    _targetSize.y = std::clamp(_targetSize.y, 1.0f, (float)SCREEN_HEIGHT);

    if (_isChangeing)
    {
        float ratio = _timer / _duration;
        float ease = GET_SINGLE(EasingManager)->OutSine(ratio);

        float xL = std::lerp(_moveStartPos.x, _destination.x, ease);
        float yL = std::lerp(_moveStartPos.y, _destination.y, ease);

        float sizeX = std::lerp(_windowSize.x, _targetSize.x, ease);
        float sizeY = std::lerp(_windowSize.y, _targetSize.y, ease);

        sizeX = std::clamp(sizeX, 1.0f, (float)SCREEN_WIDTH);
        sizeY = std::clamp(sizeY, 1.0f, (float)SCREEN_HEIGHT);

        SetSizeAndPos({ sizeX, sizeY }, { xL, yL });

        _timer += dt;
        _isChangeing = _timer <= _duration;

        return;
    }

    if (!_isRestoring)
    {
        _restoreTimer += dt;

        if (_restoreTimer >= _restoreDelay)
        {
            _isRestoring = true;
        }

        return;
    }

    if (_windowSize.x > _originSize.x ||
        _windowSize.y > _originSize.y)
    {
        _targetSize.x = std::lerp(_windowSize.x, _originSize.x, dt);
        _targetSize.y = std::lerp(_windowSize.y, _originSize.y, dt);
        SetSizeAndPos(_targetSize, _pos);

        if (fabs(_targetSize.x - _originSize.x) < 0.5f &&
            fabs(_targetSize.y - _originSize.y) < 0.5f)
        {
            SetSizeAndPos(_originSize, _pos);
            _isRestoring = false;
        }
    }
}

void GameWindow::WindowMoveAndChangeSize(const Vec2& deltaPos, const Vec2& deltaSize, const float duration)
{
    // 현재 사이즈에서, 변화량만큼 더해주기
    _targetSize += deltaSize;

    _moveStartPos = _pos;
    _destination = _pos + deltaPos;

    _timer = 0.f;
    _isChangeing = true;
    _duration = duration;
}
