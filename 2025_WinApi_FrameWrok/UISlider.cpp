#include "pch.h"
#include "UISlider.h"
#include "InputManager.h"


UISlider::UISlider(RECT barRect)
    : UIElement(barRect), _barRect(barRect)
{
    SetValue(0.5f);
}

void UISlider::SetOnValueChanged(std::function<void(float)> callback)
{
    _onValueChanged = callback;
}

void UISlider::SetValue(float value)
{
    _value = std::clamp(value, 0.0f, 1.0f);

    int width = _barRect.right - _barRect.left;
    int height = _barRect.bottom - _barRect.top;

    int fillRight = static_cast<int>(_barRect.left + (_value * width));
    _fillRect = { _barRect.left, _barRect.top, fillRight, _barRect.bottom };

    int handleWidth = 12;
    int handleHeight = height + 6;

    int handleX = fillRight - handleWidth / 2;
    int handleY = _barRect.top - 3;
    _handleRect = { handleX, handleY, handleX + handleWidth, handleY + handleHeight };
}

void UISlider::Render(HDC hdc)
{
    HBRUSH bgBrush = CreateSolidBrush(RGB(200, 200, 200));
    FillRect(hdc, &_barRect, bgBrush);
    DeleteObject(bgBrush);

    HBRUSH fillBrush = CreateSolidBrush(RGB(100, 180, 255));
    FillRect(hdc, &_fillRect, fillBrush);
    DeleteObject(fillBrush);

    HBRUSH handleBrush = CreateSolidBrush(RGB(50, 50, 200));
    FillRect(hdc, &_handleRect, handleBrush);
    DeleteObject(handleBrush);
}

void UISlider::Update()
{
    const POINT& mouse = GET_SINGLE(InputManager)->GetMousePos();

    bool down = GET_SINGLE(InputManager)->IsDown(KEY_TYPE::LBUTTON);
    bool press = GET_SINGLE(InputManager)->IsPress(KEY_TYPE::LBUTTON);

    if (!_dragging)
    {
        if (press)
        {
            if (PtInRect(&_handleRect, mouse) || PtInRect(&_barRect, mouse))
            {
                _dragging = true;

                int barWidth = _barRect.right - _barRect.left;
                float newVal = (mouse.x - _barRect.left) / (float)barWidth;
                newVal = std::clamp(newVal, 0.0f, 1.0f);

                if (newVal != _value)
                {
                    SetValue(newVal);
                    if (_onValueChanged)
                        _onValueChanged(_value);
                }
            }
        }
    }
    else if (_dragging && press)
    {
        int barWidth = _barRect.right - _barRect.left;
        float newVal = (mouse.x - _barRect.left) / (float)barWidth;
        newVal = std::clamp(newVal, 0.0f, 1.0f);

        if (newVal != _value)
        {
            SetValue(newVal);
            if (_onValueChanged)
                _onValueChanged(_value);
        }
    }

    if (!press)
    {
        _dragging = false;
    }
}

