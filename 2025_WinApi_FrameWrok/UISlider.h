#pragma once
#include "UIElement.h"

class UISlider : public UIElement
{
public:
    UISlider(RECT barRect);
    void SetValue(float value);
    float GetValue() const { return _value; }
    void SetOnValueChanged(std::function<void(float)> callback);

    void Render(HDC hdc) override;
    void Update() override;

private:
    RECT _barRect;
    RECT _fillRect;
    RECT _handleRect;

    float _value = 0.0f;
    bool _dragging = false;

    std::function<void(float)> _onValueChanged;
};
