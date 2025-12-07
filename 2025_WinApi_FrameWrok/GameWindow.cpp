#include "pch.h"
#include "GameWindow.h"
#include "EasingManager.h"

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

    if (_isChangeing)
    {

        float ratio = _timer / _duration;
        float ease = GET_SINGLE(EasingManager)->OutSine(ratio);

        float xL = std::lerp(_moveStartPos.x, _destination.x, ease);
        float yL = std::lerp(_moveStartPos.y, _destination.y, ease);
        
        xL = std::clamp(xL, _size.x * 0.5f, SCREEN_WIDTH - _size.x * 0.5f);
        yL = std::clamp(yL, _size.y * 0.5f, SCREEN_HEIGHT - _size.y * 0.5f);

        float sizeX = std::lerp(_windowSize.x, _targetSize.x, ease);
        float sizeY = std::lerp(_windowSize.y, _targetSize.y, ease);

        SetSizeAndPos({sizeX, sizeY}, { xL, yL });
        
        _timer += dt;
        _isChangeing = _timer <= _duration;

        if (!_isChangeing)
        {
            _restoreTimer = 0;
            _isRestoring = false;
        }

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
