#include "pch.h"
#include "InputManager.h"
#include "Core.h"

void InputManager::Init()
{
    _vecKey.resize((int)KEY_TYPE::LAST, KeyInfo{ KEY_STATE::NONE, false});
   
    _mousePos = {};
    _prevMousePos = _mousePos;
    _mouseDelta = {};
    
    for (int i = 0; i < (int)KEY_TYPE::LALT; ++i)
    {
        assert(_vkKey[i] != 0 && "Key type, vKey 매핑 에러");
    }
}


void InputManager::Update()
{
    HWND hWnd = ::GetFocus();
    if (hWnd == nullptr)
    {
        ResetAll();
        return;
    }

	UpdateKeys();
    UpdateMouse(hWnd);
}

void InputManager::UpdateKeys()
{
    for (int i = 0; i < (int)KEY_TYPE::LAST; i++)
    {
        const bool pressed = (::GetAsyncKeyState(_vkKey[i]) & 0x8000) != 0;
        auto& key = _vecKey[i];

        if (pressed)
        {
            key.state = key.isPrevCheck ? KEY_STATE::PRESS : KEY_STATE::DOWN;
            key.isPrevCheck = true;
        }
        else
        {
            key.state = key.isPrevCheck ? KEY_STATE::UP : KEY_STATE::NONE;
            key.isPrevCheck = false;
        }
    }
}

void InputManager::UpdateMouse(HWND hWnd)
{
    ::GetCursorPos(&_mousePos);
    ::ScreenToClient(hWnd, &_mousePos);

    RECT rt;
    ::GetWindowRect(hWnd, &rt);
    _mousePos.x += rt.left;
    _mousePos.y += rt.top;

    _mouseDelta.x = _mousePos.x - _prevMousePos.x;
    _mouseDelta.y = _mousePos.y - _prevMousePos.y;
    _prevMousePos = _mousePos;
}

void InputManager::ResetAll()
{
    for (auto& e : _vecKey)
    {
        e.isPrevCheck = false;
        e.state = KEY_STATE::NONE;
    }

    // mouse
    ::GetCursorPos(&_mousePos);
    ::ScreenToClient(GET_SINGLE(Core)->GetHwnd(), &_mousePos);
    _prevMousePos = _mousePos;
    _mouseDelta = { 0,0 };
}
